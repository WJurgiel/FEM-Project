//
// Created by Wojtek on 24.10.2024.
//

#include "../Includes/Element.h"

Element::Element(int id, Vector<int> nodeIDs) {
    this->id = id;
    this->nodeIDs = nodeIDs;


}

// void Element::populateJacobians(int idInteg, Matrix<double> dN_dEta, Matrix<double> dN_dKsi, Vector<Node> elemNodes) {
//
// }
