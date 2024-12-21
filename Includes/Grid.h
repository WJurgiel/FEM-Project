//
// Created by Wojtek on 24.10.2024.
//

#ifndef GRID_H
#define GRID_H

#include <ElemUniv.h>
#include <ranges>

#include "Includes.h"
#include "Node.h"
#include "Element.h"
#include "GlobalData.h"


using File = std::ifstream;
class Grid {
private:
    // Note: the calculations are made only for quadrangle elements
    Vector<Node> nodes;
    Vector<Element> elements;
    GlobalData globalData;

    Vector<Node> integrationPoints;
    Vector<double> wages;

    ElemUniv& m_elem_univ;

    int nip;
public:
    // Always call this function in the constructor -> without it elements won't know their nodes
    void assignStartTemperature();
    void assignNodesToElements();
    void executeCalculations(Matrix<double>&, Matrix<double>&);
    // Use when you want to execute calculations for specific element (possibly for multithreading)
    void executeCalculations(Matrix<double>&, Matrix<double>&, int elementID);

    //Constructors:
    //Please use this constructor when you are testing the program on custom values
    Grid(Vector<Node> integrationPoints, Vector<double> wages, ElemUniv& elem_univ);

    // Please use this constructor when you want to make calculations with data from file
    /*normalize parameter = if input file has indexing starting with 1, type 1, if it's normal
            indexing convention (start id=0) type 0
    */
    Grid(Vector<Node> integrationPoints,  Vector<double> wages,std::string fileName, ElemUniv& elem_univ, int normalize=1);

    // Getters:
    int getNip() const;
    Vector<Node> getIntegrationPoints() const;
    std::size_t getElementCount() const;
    Element getElement(int id) const;
    Vector<Node> getNodes() const;

    friend std::ostream& operator<<(std::ostream& os, const Grid& grid);
};

inline std::ostream& operator<<(std::ostream& os, const Grid& grid) {
    os << "Nodes:\n";
    for(const auto& node: grid.nodes) {
        os << node;
    }
    for(const auto& elem : grid.elements) {
         os << elem << "\n";
    }
    os << grid.globalData << "\n";

    os<< "Integration points:\n";
    for(const auto& point: grid.integrationPoints) {
        os << point;
    }
    os << "Number of integration points: " << grid.nip;
    return os;
}


#endif //GRID_H
