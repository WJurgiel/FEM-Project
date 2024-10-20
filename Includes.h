#pragma once
#include <fstream>
#include <vector>
#include <filesystem>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <thread>
#include <atomic>

using Matrix = std::vector<std::vector<double>>;

inline std::ostream& operator<<(std::ostream& os, const Matrix& matrix){
    int cnt = 0;
    for(const auto& row: matrix) {
        std::cout << "[ "  << cnt++ << " ]: ";
        std::cout << std::setw(10);
        for(const auto& elem: row) {
            os << elem << "\t";
        }
        os << "\n";
    }
    return os;
}