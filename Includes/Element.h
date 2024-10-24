//
// Created by Wojtek on 24.10.2024.
//

#ifndef ELEMENT_H
#define ELEMENT_H

#include "Includes.h"
#include "Jacobian.h"
#include "Node.h"


class Element {
    int id;
    Vector<int> nodeIDs;
    Vector<Node> nodes;
public:
    Element(int id, Vector<int> nodeIDs);

    Vector<Jacobian> jacobianConstantsMatrixes; // each jacobian matrix for each of the integration points
    void populateJacobians(int idInteg, Matrix<double> dN_dEta, Matrix<double> dN_dKsi,  Vector<Node> elemNodes);
    //H value
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
