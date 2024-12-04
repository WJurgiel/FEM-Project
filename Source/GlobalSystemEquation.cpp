//
// Created by Wojtek on 20.11.2024.
//

#include "GlobalSystemEquation.h"

#include "FileHandler.h"

std::ostream& operator<<(std::ostream& os, const GlobalSystemEquation& eqn) {
    for(auto x : eqn.H_global) {
        for (auto y : x) {
            os << y << " ";
        }
        os << std::endl;
    }
    return os;
}
