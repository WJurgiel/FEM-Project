//
// Created by Wojtek on 20.11.2024.
//

#include "GlobalSystemEquation.h"

#include "FileHandler.h"

std::ostream& operator<<(std::ostream& os, const GlobalSystemEquation& eqn) {
    os << "H Global:\n";
    for(auto x : eqn.H_global) {
        for (auto y : x) {
            os << y << " ";
        }
        os << "\n";
    }
    os << "\nP Global:\n";
    for(const auto& x : eqn.P_global) {
        os << x << " ";
    }
    os << "\n";
    os << "C Global:\n";
    for(auto x : eqn.C_global) {
        for (auto y : x) {
            os << y << " ";
        }
        os << "\n";
    }
    return os;
}

void GlobalSystemEquation::solveT() {
    T_vector = gaussElimination(H_global,P_global);
    std::cout<< "Vector T:\n";
    std::cout << T_vector;
}
void GlobalSystemEquation::solveSimulation(Grid& grid) {
    int simulationTime = grid.getGlobalData().getParameter("SimulationTime");
    int stepTime = grid.getGlobalData().getParameter("SimulationStepTime");
    double initTemp = grid.getGlobalData().getParameter("InitialTemp");

    int nodeCount = grid.getNodes().size();

    Matrix<double> leftSide(nodeCount, Vector<double>(nodeCount,0.0));
    Vector<double> rightSide(nodeCount, 0.0);
    Vector<double> t0(nodeCount, initTemp);

    grid.updateNodesTemperatures(t0);
    std::cout << "-------------------------------------------\n";
    std::cout << "min max for timestamp (s)\n";
    for(int step=0; step < simulationTime; step+=stepTime) {
        std::fill(rightSide.begin(), rightSide.end(), 0.0);
        for(int row = 0; row < nodeCount; row++) {
            for(int col = 0; col < nodeCount; col++) {
                leftSide[row][col] = (C_global[row][col] / stepTime) + H_global[row][col];
                rightSide[row] += (C_global[row][col] / stepTime) * t0[col];
            }
            rightSide[row] += P_global[row];
        }
        double maxTemp = -INT_MAX;
        double minTemp = INT_MAX;
        t0 = gaussElimination(leftSide,rightSide);
        for(int i = 0; i < nodeCount; i++) {
            maxTemp = std::max(maxTemp,t0[i]);
            minTemp = std::min(minTemp,t0[i]);
        }
        grid.updateNodesTemperatures(t0);
        std::cout << step << ": "  << "<MIN: " << minTemp << "  MAX: " << maxTemp << ">\n";
    }
    std::cout << "-------------------------------------------\n";


}

