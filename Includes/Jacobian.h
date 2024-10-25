//
// Created by Wojtek on 24.10.2024.
//

#ifndef JACOBIAN_H
#define JACOBIAN_H

#include "Includes.h"
#include "Node.h"
//DLA POSZCZEGÓLNEGO PUNKTU CAŁKOWANIA N
class Jacobian {
private:
    double determinant;
    Matrix<double> jacobianMatrix;
    Matrix<double> jacobianInverseMatrix;
    Matrix<double> jacobianFinal;

public:
    Jacobian();

    void calculateJacobianMatrix(int idIntegPoint, Matrix<double>& dN_dEta, Matrix<double>& dN_dKsi,  Vector<Node> elemNodes);
    void calculateJacobianInverseMatrix();
    void calculateDeterminant();
    void calculateJacobianFinal();

    // void executeJacobianMatrix();
    double getDeterminant() const;
    Matrix<double> getJacobianFinal() const;
    friend std::ostream& operator<<(std::ostream& os, const Jacobian& jacobian);
};

inline std::ostream& operator<<(std::ostream& os, const Jacobian& jacobian) {
    os << "DET:\n" << jacobian.determinant << "\n";
    // os << "Jacobian matrix:\n";
    // for(auto& x: jacobian.jacobianMatrix) {
    //     for(auto& y: x) {
    //         os << y << "\t";
    //     }
    //     os << "\n";
    // }
    // os << "Jacobian inversed matrix: ";
    // for(auto& x: jacobian.jacobianInverseMatrix) {
    //     for(auto& y: x) {
    //         os << y << "\t";
    //     }
    //     os << "\n";
    // }
    os << "Jacobian final matrix:\n";
    for(auto& x: jacobian.jacobianFinal) {
        for(auto& y: x) {
            os << y << "\t";
        }
        os << "\n";
    }
    os << "--------------------\n";
    return os;
}


#endif //JACOBIAN_H
