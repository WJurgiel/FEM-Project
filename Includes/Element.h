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
    Matrix<double> H_matrix;

    void populateJacobians(int nip, Matrix<double> dN_dEta, Matrix<double> dN_dKsi,  Vector<Node> elemNodes);
    void calculate_dN_dx_dy(int npc, Matrix<double> dN_dEta, Matrix<double> dN_dKsi);

    void printJacobians(int nip);
    void printMatrix(Matrix<double>);


    friend std::ostream& operator<<(std::ostream& os, const Element& e);
};
inline std::ostream& operator<<(std::ostream& os, const Element& e) {
    os << "Element [" << e.id << "]: ";
    for(auto &n : e.nodeIDs) {
        os << n << " ";
    }
    os << "\n";
    return os;
}



#endif //ELEMENT_H
