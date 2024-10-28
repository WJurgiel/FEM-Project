//
// Created by Wojtek on 24.10.2024.
//

#ifndef ELEMENT_H
#define ELEMENT_H

#include "Includes.h"
#include "Jacobian.h"
#include "Node.h"

// The encapsulation problem will be potentially solved soon...
class Element {
    int id;
    Vector<int> nodeIDs;
    Vector<Node> nodes; // I think I haven't implemented it yet
public:
    Element(int id, Vector<int> nodeIDs);

    Vector<Jacobian> jacobianConstantsMatrixes; // each jacobian matrix for each of the integration points

    Matrix<double> dN_dx;
    Matrix<double> dN_dy;
    Vector<Matrix<double>> H_matrixes; // contains H_matrix for each of integration points
    Matrix<double> H_final;

    void calculateJacobians(int nip, Matrix<double> dN_dEta, Matrix<double> dN_dKsi,  Vector<Node> elemNodes);
    void calculate_dN_dx_dy(int npc, Matrix<double> dN_dEta, Matrix<double> dN_dKsi);
    void calculate_H_matrix(int nip,double conductivity, Vector<double> ipDeterminates);
    ///Well we don't know how wages are determined yet.
    void calculate_H_final(int nip, Vector<double> wages);
    void printJacobians(int nip);
    void printMatrix(Matrix<double>);

    Vector<int> getNodeIDs();
    void setNodes(Vector<Node>);
    friend std::ostream& operator<<(std::ostream& os, const Element& e);

};
inline std::ostream& operator<<(std::ostream& os, const Element& e) {
    os << "Element [" << e.id << "]: ";
    for(auto &n : e.nodeIDs) {
        os << n << " ";
    }
    std::cout << "contains nodes:\n";
    for(auto &n : e.nodes) {
        os << n << " ";
    }
    os << "\n";
    return os;
}



#endif //ELEMENT_H
