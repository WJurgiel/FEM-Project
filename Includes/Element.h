//
// Created by Wojtek on 24.10.2024.
//

#ifndef ELEMENT_H
#define ELEMENT_H

#include "Includes.h"
#include "Node.h"


class Element {
    int id;
    Vector<int> nodeIDs;
    Vector<Node> nodes;
public:
    Element(int id, Vector<int> nodeIDs);

    //Jacobian
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
