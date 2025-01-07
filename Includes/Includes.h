//
// Created by Wojtek on 24.10.2024.
//

#ifndef INCLUDES_H
#define INCLUDES_H

#define X 0
#define Y 1
#define ETA 0
#define KSI 1


// CONFIG
#define DEBUGINFO 0
#define CALCULATIONS 1
#define MULTITHREADING 0

#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <string>
#include <unordered_map>
#include <fstream>

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
inline Vector<double> operator*(const double& n, const Vector<double>& vec) {
    Vector<double> result(vec.size());
    for(size_t i = 0; i < vec.size(); ++i) {
        result[i] = n * vec[i];
    }
    return result;
}
inline Vector<double> operator+(const Vector<double>& a, const Vector<double>& b) {
    Vector<double> result(a.size());
    for(size_t i = 0; i < a.size(); ++i) {
        result[i] = a[i] + b[i];
    }
    return result;
}
inline Vector<std::string> split(const std::string& str, char delim) {
    std::stringstream ss(str);
    std::string token;
    Vector<std::string> tokens;
    while(std::getline(ss,token,delim)) {
        tokens.push_back(token);
    }
    return tokens;

}
template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat) {
    for(const auto& row : mat) {
        for(const auto& col : row) {
            os << col << " ";
        }
        os << "\n";
    }
    return os;
}
template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
    for(const auto& elem : vec) {
        os << elem << " ";
    }
    os<<"\n";
    return os;
}
#endif //INCLUDES_H
