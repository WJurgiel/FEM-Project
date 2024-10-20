//
// Created by Wojtek on 19.10.2024.
//

#include "JacobiMethod.h"

//TODO: class containing all the possible 2D integration points

JacobiMethod::JacobiMethod(Matrix integratonPoints) {
    this->integrationPoints = integratonPoints;
    this->npc = static_cast<int>(integratonPoints.size());
    dn_i_dEta = Matrix(npc, std::vector<double>(4,0.0));
    dn_i_dKsi = Matrix(npc, std::vector<double>(4,0.0));
}

void JacobiMethod::populateDnEta(Matrix& dn_i_dEta, Matrix integPoints) const {
    for(auto ip = 0; ip < npc; ip++) { // ip - integration point
        dn_i_dEta[ip][0] = -0.25 * (1 - integPoints[ip][KSI]);
        dn_i_dEta[ip][1] = 0.25 * (1 - integPoints[ip][KSI]);
        dn_i_dEta[ip][2] = 0.25 * (1 + integPoints[ip][KSI]);
        dn_i_dEta[ip][3] = -0.25 * (1 + integPoints[ip][KSI]);
    }
}

void JacobiMethod::populateDnKsi(Matrix& dn_i_dKsi, Matrix integPoints) const {
    for(auto ip = 0; ip < npc; ip++) { // ip - integration point
        dn_i_dKsi[ip][0] = -0.25 * (1 - integPoints[ip][ETA]);
        dn_i_dKsi[ip][1] = -0.25 * (1 + integPoints[ip][ETA]);
        dn_i_dKsi[ip][2] = 0.25 * (1 + integPoints[ip][ETA]);
        dn_i_dKsi[ip][3] = 0.25 * (1 - integPoints[ip][ETA]);
    }
}

void JacobiMethod::populateJacobiMatrix(Matrix& dn_i_matrix) {
    /*
     * Jacobi matrix
     *          0           1
     *  0    dx/dEta     dy/dEta
     *  1    dx/dKsi     dy/dKsi
     *
     */

    for(int i = 0 ; i < 4; i++) {
        jacobian[ETA][X] += dn_i_dEta[0][i] * exampleData[i][X];
        jacobian[ETA][Y] += dn_i_dEta[0][i] * exampleData[i][Y];
    }
    for(int i = 0 ; i < 4; i++) {
        jacobian[KSI][X] += dn_i_dKsi[0][i] * exampleData[i][X];
        jacobian[KSI][Y] += dn_i_dKsi[0][i] * exampleData[i][Y];
    }
}

double JacobiMethod::calculateDetJacobi(Matrix &jacobian) {
    return jacobian[ETA][X] * jacobian[KSI][Y] - jacobian[ETA][Y] * jacobian[KSI][X];
}

void JacobiMethod::populateJacobi1() {
    jacobian1 = jacobian;
    jacobian1[ETA][X] = jacobian[KSI][Y];
    jacobian1[KSI][Y] = jacobian[ETA][X];
    jacobian1[ETA][Y] *= -1;
    jacobian[KSI][X] *= -1;
}

// double JacobiMethod::calculateDetJacobi() {
// }

void JacobiMethod::executeJacobiMethod() {
    populateDnEta(dn_i_dEta, integrationPoints);
    populateDnKsi(dn_i_dKsi, integrationPoints);
    populateJacobiMatrix(jacobian);
    populateJacobi1();
    determinant = calculateDetJacobi(jacobian);
}

void JacobiMethod::getOutput() const {
    std::cout << std::setw(10) << "pc/\tdN0_d/Eta\tdN1_d/Eta\tdN2_d/Eta\tdN3_d/Eta\n";
    std::cout << "----------------------------------------------------------------\n";
    std::cout << dn_i_dEta;
    std:: cout << "\n";
    std::cout << std::setw(10) << "pc/\tdN0_d/Ksi\tdN1_d/Ksi\tdN2_d/Ksi\tdN3_d/Ksi\n";
    std::cout << "-----------------------------------------------------------------\n";
    std::cout << dn_i_dKsi;

    std::cout << "Jakobian:\n";
    std::cout << jacobian;

    std::cout << "Jakobian ^ - 1:\n";
    std::cout << jacobian1;

    std::cout << "Det[J]: " << determinant;
}

Matrix JacobiMethod::getJacobiMatrix() const {
    return jacobian;
}

Matrix JacobiMethod::getJacobiMatrix1() const {
    return jacobian1;
}

double JacobiMethod::getJacobiDeterminant() const {
    return determinant;
}
