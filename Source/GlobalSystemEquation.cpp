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
    return os;
}
