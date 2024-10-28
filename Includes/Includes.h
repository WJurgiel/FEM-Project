//
// Created by Wojtek on 24.10.2024.
//

#ifndef INCLUDES_H
#define INCLUDES_H

#define X 0
#define Y 1
#define ETA 0
#define KSI 1

#include <iostream>
#include <vector>
#include <iomanip>
#include <unordered_map>

template <typename T>
    using Matrix = std::vector<std::vector<T>>;

template <typename T>
    using Vector = std::vector<T>;

inline Matrix<double> operator+(const Matrix<double>& a, const Matrix<double>& b) {
    if (a.size() != b.size() || (a.size() > 0 && a[0].size() != b[0].size())) {
        throw std::invalid_argument("Matrices must be the same size to add.");
    }
    Matrix<double> result(a.size(), Vector<double>(a[0].size()));

    for (size_t i = 0; i < a.size(); ++i) {
        for (size_t j = 0; j < a[i].size(); ++j) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }

    return result;
}

inline Matrix<double> operator*(const double& n, const Matrix<double>& mat) {
    Matrix<double> result(mat.size(), Vector<double>(mat[0].size()));
    for(size_t i = 0; i < mat.size(); ++i) {
        for(size_t j = 0; j < mat[i].size(); ++j) {
            result[i][j] = n * mat[i][j];
        }
    }
    return result;
}

#endif //INCLUDES_H
