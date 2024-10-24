//
// Created by Wojtek on 24.10.2024.
//

#ifndef GRID_H
#define GRID_H

#include <ranges>

#include "Includes.h"
#include "Node.h"
#include "Element.h"
#include "GlobalData.h"
class Grid {
public:
    Vector<Node> nodes;
    Vector<Element> elements;
    GlobalData globalData;

    Grid(Vector<Node> integrationPoints);
    Vector<Node> integrationPoints;
    int nip;

    friend std::ostream& operator<<(std::ostream& os, const Grid& grid);
};
inline std::ostream& operator<<(std::ostream& os, const Grid& grid) {
    os << "Nodes:\n";
    for(auto& node: grid.nodes) {
        os << node;
    }
    for(auto& elem : grid.elements) {
         os << elem << "\n";
    }
    os << grid.globalData << "\n";

    os<< "Integration points:\n";
    for(auto& point: grid.integrationPoints) {
        os << point;
    }
    os << "Number of integration points: " << grid.nip;
    return os;
}


#endif //GRID_H
