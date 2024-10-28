//
// Created by Wojtek on 24.10.2024.
//

#include "../Includes/Element.h"


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

void Element::calculate_H_matrix(int nip, double conductivity, Vector<double> ipDeterminates) {
    H_matrixes.resize(nip);
    for(int ip = 0; ip < nip; ip++) {
        H_matrixes[ip].resize(nip, Vector<double>(4));
        Vector<double> dNi_dx(dN_dx[ip]);
        Vector<double> dNi_dy(dN_dy[ip]);
        Matrix<double> L_dN_dx_mat(nip, Vector<double>(4)); // {dN/dx}{dN/dx}^T
        Matrix<double> R_dN_dy_mat(nip, Vector<double>(4)); //{dN/dy}{dN/dy}^T
        int size = static_cast<int>(dNi_dx.size()); // universal size for dNi_dx and dNi_dNy
        //calculate {dN/dx}{dN/dx}^T and {dN/dy}{dN/dy}^T
        for(int row = 0;  row < size;  row++) {
            for(int col = 0; col < size; col++) {
                L_dN_dx_mat[row][col] = dNi_dx[row] * dNi_dx[col];
                R_dN_dy_mat[row][col] = dNi_dy[row] * dNi_dy[col];
            }
        }
        H_matrixes[ip] = conductivity * (L_dN_dx_mat + R_dN_dy_mat);
        H_matrixes[ip] = ipDeterminates[ip] * H_matrixes[ip];
        //To do:
        // multiply the matrixes by wages

    }
}

void Element::calculate_H_final(int nip, Vector<double> wages) {
    H_final.resize(H_matrixes[0].size(), Vector<double>(H_matrixes[0][0].size()));
    H_final = wages[0] * wages[0]* H_matrixes[0] + wages[1]*wages[0] * H_matrixes[1] + wages[1]*wages[0]*H_matrixes[2] + wages[1]*wages[1] * H_matrixes[3];
}

void Element::printJacobians(int nip) {
    for(int ip = 0; ip < nip; ip++) {
        std::cout << "Integ point " << ip << ": " << jacobianConstantsMatrixes[ip];
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

Vector<int> Element::getNodeIDs() {
    return nodeIDs;
}

void Element::setNodes(Vector<Node> nodes) {
    this->nodes = nodes;
}



