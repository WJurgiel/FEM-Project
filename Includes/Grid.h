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


using File = std::ifstream;
class Grid {
private:
    static void clearFile(std::string);
public:
    //Contains information about all the nodes
    //Contains information about all the elements - each element has its nodes
    Vector<Node> nodes;
    Vector<Element> elements;
    GlobalData globalData;

    void assignNodesToElements();
    //
    void executeCalculations(Matrix<double>&, Matrix<double>&);
    // Integration points data
    /*normalize = if input file has indexing starting with 1, type 1, if it's normal
        indexing convention (start id=0) type 0
    */
    Grid(Vector<Node> integrationPoints, Vector<double> wages);
    Grid(Vector<Node> integrationPoints,  Vector<double> wages,std::string fileName, int normalize=1);
    Vector<Node> integrationPoints;
    Vector<double> wages;
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
