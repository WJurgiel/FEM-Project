//
// Created by Wojtek on 24.10.2024.
//

#include "Element.h"

#include <ElemUniv.h>


Element::Element(int id, Vector<int> nodeIDs) {
    this->id = id;
    this->nodeIDs = nodeIDs;


}

void Element::calculateJacobians(int nip, Matrix<double> dN_dEta, Matrix<double> dN_dKsi, Vector<Node> elemNodes) {
    for(int ip = 0; ip < nip; ip++) {
        this->jacobianConstantsMatrixes.push_back(Jacobian());
        this->jacobianConstantsMatrixes[ip].calculateJacobianMatrix(ip, dN_dEta, dN_dKsi, elemNodes);
        this->jacobianConstantsMatrixes[ip].calculateDeterminant();
        this->jacobianConstantsMatrixes[ip].calculateJacobianInverseMatrix();
        this->jacobianConstantsMatrixes[ip].calculateJacobianFinal();
    }
}

// pytanie do prowadzacego: czy ilosc funkcji ksztaltu jest stala? czy np majac trojkatny element są 3 funkcje ksztaltu?
void Element::calculate_dN_dx_dy(int nip, Matrix<double> dN_dEta, Matrix<double> dN_dKsi) {
    dN_dx.resize(nip, Vector<double>(4));
    dN_dy.resize(nip, Vector<double>(4));

    for(int ip = 0; ip < nip; ip++) {
        Matrix<double> jacobian = jacobianConstantsMatrixes[ip].getJacobianFinal();
        for(auto Ni = 0; Ni < 4; Ni++) {
            dN_dx[ip][Ni] = jacobian[0][0] * dN_dEta[ip][Ni] + jacobian[0][1] * dN_dKsi[ip][Ni];
            dN_dy[ip][Ni] = jacobian[1][0] * dN_dEta[ip][Ni] + jacobian[1][1] * dN_dKsi[ip][Ni];
        }


    }
}

void Element::calculate_H_matrix(int nip, double conductivity) {
    H_matrixes.resize(nip);
    for(int ip = 0; ip < nip; ip++) {
        H_matrixes[ip].resize(4, Vector<double>(4));
        Vector<double> dNi_dx(dN_dx[ip]);
        Vector<double> dNi_dy(dN_dy[ip]);
        Matrix<double> L_dN_dx_mat(4, Vector<double>(4)); // {dN/dx}{dN/dx}^T
        Matrix<double> R_dN_dy_mat(4, Vector<double>(4)); //{dN/dy}{dN/dy}^T
        int size = static_cast<int>(dNi_dx.size()); // universal size for dNi_dx and dNi_dNy
        //calculate {dN/dx}{dN/dx}^T and {dN/dy}{dN/dy}^T
        for(int row = 0;  row < size;  row++) {
            for(int col = 0; col < size; col++) {
                L_dN_dx_mat[row][col] = dNi_dx[row] * dNi_dx[col];
                R_dN_dy_mat[row][col] = dNi_dy[row] * dNi_dy[col];
            }
        }
        H_matrixes[ip] = conductivity * (L_dN_dx_mat + R_dN_dy_mat);
        H_matrixes[ip] = jacobianConstantsMatrixes[ip].getDeterminant() * H_matrixes[ip];
    }
}

void Element::calculate_HBC_matrix(int nip, double conductivity, ElemUniv& elem_univ) {
    // for every surface
        // check if has BC
    // ElemUniv elem_univ()
    //surface integration point count (n)
    H_BC.resize(4, std::vector<double>(4, 0.0));
    int nsip = static_cast<int>(sqrt(nip));

    // N matrixes calculations - WORKS
    for(int _surfID = 0; _surfID < 4; _surfID++ ) {
        std::cout << "SURFACE: " << _surfID << std::endl;
        elem_univ.surfaces[_surfID].N = Matrix<double>(nsip, Vector<double>(4));
        for(int _sip = 0; _sip < nsip; _sip++) {
            double eta = elem_univ.surfaces[_surfID].surfaceIntegPoints[_sip].getX();
            double ksi = elem_univ.surfaces[_surfID].surfaceIntegPoints[_sip].getY();
            std::cout << "Sip" << _sip << "Ksi: " << eta << " Eta: " << ksi << "\n";
            elem_univ.surfaces[_surfID].N[_sip][0] = 0.25 * (1 - eta) * (1 - ksi);
            elem_univ.surfaces[_surfID].N[_sip][1] = 0.25 * (1 + eta) * (1 - ksi);
            elem_univ.surfaces[_surfID].N[_sip][2] = 0.25 * (1 + eta) * (1 + ksi);
            elem_univ.surfaces[_surfID].N[_sip][3] = 0.25 * (1 - eta) * (1 + ksi);
        }
        std::cout << elem_univ.surfaces[_surfID].N;
        std::cout << "\n";
    }

    // calculate L (length) for jacobian for every surface
    // top: 0 1, left 1 2, bottom 2 3, right 3 0 - WORKS
    std::cout << "Lengths:";
    std::pair<int,int> edgeIDs = {0,1};
    for(int _surfID = Surfaces::TOP; _surfID < 4; _surfID++) {
        std::cout << "first edge: " << edgeIDs.first << " second edge: " << edgeIDs.second << std::endl;
        elem_univ.surfaces[_surfID].surfaceLength = sqrt(
              pow(nodes[edgeIDs.first].getX() - nodes[edgeIDs.second].getX(), 2) +
                  pow(nodes[edgeIDs.first].getY() - nodes[edgeIDs.second].getY(), 2)
                  );
        edgeIDs.first++;
        edgeIDs.second = (edgeIDs.second >= Surfaces::RIGHT) ? 0 : edgeIDs.second + 1;
        std::cout << "Surface " << _surfID << ": " << elem_univ.surfaces[_surfID].surfaceLength << "\n";
    }

    //calculate HBC
    /*
     * ISSUE: HBc local not calculated properly
     */
    Matrix<double> HBC_local(4, Vector<double>(4));
    for(int _surfID = 0; _surfID < 4; _surfID++) {
        for(int _sip = 0; _sip < nsip; _sip++) {
            Matrix<double> L_N_mat(4, Vector<double>(4)); // {N}{N}^T
            Matrix<double> R_N_mat(4, Vector<double>(4)); //{N}{N}^T
            Matrix<double> N = elem_univ.surfaces[_surfID].N;
            for(int row = 0;  row < 4;  row++) {
                for(int col = 0; col < 4; col++) {
                    L_N_mat[row][col] = N[_sip][row] * N[_sip][col];
                    R_N_mat[row][col] = N[_sip][row] * N[_sip][col];
                }
            }
            HBC_local = 25 * 1 * L_N_mat + R_N_mat;
            // 1 is currently a wage taken from IntegrationPoints.constWages taken for 4 (2) integration points
            //m_sideLength / 2 = det(jac)
            // det(jac) * w * HbcLocal
            double jac = elem_univ.surfaces[_surfID].surfaceLength / 2;
            std::cout << "Jakobian: " << jac << "\n";
            HBC_local = jac * 1 * HBC_local;
            std::cout << "Surface " << _surfID << " pc " << _sip << ": \n" <<  HBC_local;
            //Add to m_HBC
            H_BC = H_BC + HBC_local;
        }
    }

}

void Element::calculate_H_final(int nip, Vector<double> wages) {
    H_final.resize(H_matrixes[0].size(), Vector<double>(H_matrixes[0][0].size()));

    for(int ip = 0; ip < nip; ip++) {
        H_final = H_final + (wages[ip % wages.size()]* wages[ip / wages.size()] * H_matrixes[ip]);
    }

}

void Element::printJacobians(int nip) const {
    for(int ip = 0; ip < nip; ip++) {
        std::cout << "Integ point " << ip << ":\n" << jacobianConstantsMatrixes[ip] << "\n";
    }
}
void Element::printMatrix(Matrix<double> matrix) {

    for(auto x : matrix) {
        for(auto y : x)
            std::cout << y << std::setw(10) << " ";
        std::cout << "\n";
    }
    std::cout << "-----------------\n";
}

Vector<int> Element::getNodeIDs() const {
    return nodeIDs;
}


Vector<Node> Element::getNodes() const {
    return nodes;
}

Matrix<double> Element::getdN_dx() const {
    return dN_dx;
}

Matrix<double> Element::getdN_dy() const {
    return dN_dy;
}

Matrix<double> Element::getH_matrixes(int ip) const {
    return H_matrixes[ip];
}

Vector<Jacobian> Element::getJacobianConstantsMatrixes() const {
    return jacobianConstantsMatrixes;
}

Vector<Matrix<double>> Element::getH_matrixes() const {
    return H_matrixes;
}

Matrix<double> Element::getH_final() const {
    return H_final;
}

int Element::getID() const {
    return id;
}


void Element::setNodes(Vector<Node> nodes) {
    this->nodes = nodes;
}

