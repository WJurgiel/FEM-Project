//
// Created by Wojtek on 24.10.2024.
//

#include "Element.h"

#include <ElemUniv.h>


Element::Element(int id, Vector<int> nodeIDs, Vector<double>& wages) : wages(wages) {
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

void Element::calculate_HBC_matrix(int nip, double alfa, ElemUniv& elemuniv) {
    H_BC.resize(4, std::vector<double>(4, 0.0));
    bool hasBC[4] = {false, false, false, false};
    int nsip = static_cast<int>(sqrt(nip));

    /*Bottom: Nodes [2] [3], Right: [3][0], Top[0][1], Left[1][2]*/
    for(int _surfID = Surfaces::BOTTOM; _surfID < 4; _surfID++) {
        int firstID = (2 + _surfID > 3) ? (2 + _surfID - 4) : 2+_surfID;
        int secondID = (3 + _surfID > 3) ? (3 + _surfID - 4) : 3+_surfID;
        hasBC[_surfID] = nodes[firstID].getBC() && nodes[secondID].getBC();
        std::cout << "HasBC[surfID = " << _surfID << "]" << hasBC[_surfID] << std::endl;
    }
    for(int _surfID = Surfaces::BOTTOM; _surfID < 4; _surfID++ ) {
        elemuniv.surfaces[_surfID].N = Matrix<double>(nsip, Vector<double>(4));
        for(int _sip = 0; _sip < nsip; _sip++) {
            double eta = elemuniv.surfaces[_surfID].surfaceIntegPoints[_sip].getX();
            double ksi = elemuniv.surfaces[_surfID].surfaceIntegPoints[_sip].getY();
            elemuniv.surfaces[_surfID].N[_sip][0] = 0.25 * (1 - eta) * (1 - ksi);
            elemuniv.surfaces[_surfID].N[_sip][1] = 0.25 * (1 + eta) * (1 - ksi);
            elemuniv.surfaces[_surfID].N[_sip][2] = 0.25 * (1 + eta) * (1 + ksi);
            elemuniv.surfaces[_surfID].N[_sip][3] = 0.25 * (1 - eta) * (1 + ksi);
        }
    }
    // bottom: 2 3, right 3 0, top 0 1, left 1 2 - WORKS
    std::pair<int,int> edgeIDs = {2,3};
    for(int _surfID = Surfaces::BOTTOM; _surfID < 4; _surfID++) {
        edgeIDs.first = (2 + _surfID > 3) ? (2 + _surfID - 4) : 2+_surfID;
        edgeIDs.second = (3 + _surfID > 3) ? (3 + _surfID - 4) : 3+_surfID;
        elemuniv.surfaces[_surfID].surfaceLength = sqrt(
              pow(nodes[edgeIDs.first].getX() - nodes[edgeIDs.second].getX(), 2) +
                  pow(nodes[edgeIDs.first].getY() - nodes[edgeIDs.second].getY(), 2)
                  );
    }
    for(int _surfID = Surfaces::BOTTOM; _surfID < 4; _surfID++) {
        if(!hasBC[_surfID]) {
            continue;
        }
        double jac = elemuniv.surfaces[_surfID].surfaceLength / 2;
        Matrix<double> HBC_ip(4, Vector<double>(4));
        Matrix<double> HBC_surf(4, Vector<double>(4));

        for(int _sip = 0; _sip < nsip; _sip++) {
            Vector<double> m_N_mat(4); // {N}{N}^T
            for(int i = 0; i < 4; i++) {
                m_N_mat[i] = elemuniv.surfaces[_surfID].N[_sip][i];
            }
            for(int row = 0;  row < 4;  row++) {
                for(int col = 0; col < 4; col++) {
                    HBC_ip[row][col] = m_N_mat[row] * m_N_mat[col];
                }
            }
            HBC_ip = wages[_sip] * alfa * HBC_ip;
            HBC_surf = HBC_surf + HBC_ip;
        }
        HBC_surf = jac * HBC_surf;
        H_BC = H_BC + HBC_surf;
        calculate_P_Vector(nip, _surfID, 1200, alfa, elemuniv);
    }

    // std::cout << "FINAL HBC MATRIX:\n " << H_BC;
    // std::cout << "FINAL H (WITHOUT HBC)\n" << H_final;
    std::cout << "FINAL P (WITHOUT HBC)\n" << P;
    H_final = H_final + H_BC;
    std::cout << "FINAL H\n" << H_final;

}

void Element::calculate_P_Vector(int nip, int surfID, double tot, double alfa, ElemUniv &elemUniv) {
    // P.resize(4,0);
    int nsip = static_cast<int>(sqrt(nip));
    Vector<double> P_surf(4);
    double jac = elemUniv.surfaces[surfID].surfaceLength / 2;
    std::cout << "Jaca dla P: "<< jac << "\n";
    for(int _sip = 0; _sip < nsip; _sip++) {
        Vector<double> P_sip(4);
        Vector<double> current = elemUniv.surfaces[surfID].N[_sip];
        P_sip = wages[_sip] * tot * current;
        P_surf = P_surf + P_sip;
    }
    P_surf = alfa * jac * P_surf;
    P = P + P_surf;
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

Vector<double> Element::getP() const {
    return P;
}

int Element::getID() const {
    return id;
}



void Element::setNodes(Vector<Node> nodes) {
    this->nodes = nodes;
}

