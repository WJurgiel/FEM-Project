//
// Created by Wojtek on 24.10.2024.
//

#include "../Includes/Jacobian.h"

Jacobian::Jacobian() {

}

// void Jacobian::executeJacobianMatrix() {
//
// }

void Jacobian::calculateJacobianMatrix(int idIntegPoint, Matrix<double>& dN_dEta, Matrix<double>& dN_dKsi,  Vector<Node> elemNodes) {
    jacobianMatrix.resize(2, std::vector<double>(2));
    /*
    * Jacobi matrix
    *          0           1
    *  0    dx/dEta     dy/dEta
    *  1    dx/dKsi     dy/dKsi
    *
    */
    for(int Nid = 0; Nid < 4; Nid++) { //for specific ID integration point, for nip all iterations
            jacobianMatrix[ETA][X] += dN_dEta[idIntegPoint][Nid] * elemNodes[Nid].getX();
            jacobianMatrix[ETA][Y] += dN_dEta[idIntegPoint][Nid] * elemNodes[Nid].getY();
            jacobianMatrix[KSI][X] += dN_dKsi[idIntegPoint][Nid] * elemNodes[Nid].getX();
            jacobianMatrix[KSI][Y] += dN_dKsi[idIntegPoint][Nid] * elemNodes[Nid].getY();
    }

}

void Jacobian::calculateJacobianInverseMatrix() {
    jacobianInverseMatrix.resize(2, std::vector<double>(2));
    jacobianInverseMatrix[ETA][X] = jacobianMatrix[KSI][Y];
    jacobianInverseMatrix[ETA][Y] =  -jacobianMatrix[ETA][Y];
    jacobianInverseMatrix[KSI][X] = -jacobianMatrix[KSI][X];
    jacobianInverseMatrix[KSI][Y] = jacobianMatrix[ETA][X];
}

void Jacobian::calculateDeterminant() {
    determinant = jacobianMatrix[ETA][X] * jacobianMatrix[KSI][Y] - (jacobianMatrix[ETA][Y] * jacobianMatrix[KSI][X]);
}

void Jacobian::calculateJacobianFinal() {
    jacobianFinal.resize(2, std::vector<double>(2));
    const double reversedDet = 1.0 / determinant;
    jacobianFinal[ETA][X] = reversedDet * jacobianInverseMatrix[ETA][X];
    jacobianFinal[ETA][Y] = reversedDet * jacobianInverseMatrix[ETA][Y];
    jacobianFinal[KSI][X] = reversedDet * jacobianInverseMatrix[KSI][X];
    jacobianFinal[KSI][Y] = reversedDet * jacobianInverseMatrix[KSI][Y];
}

double Jacobian::getDeterminant() const {
    return determinant;
}

Matrix<double> Jacobian::getJacobianFinal() const {
    return jacobianFinal;
}
