//
// Created by Wojtek on 08.11.2024.
//
#include "Includes.h"
#include "Node.h"
#ifndef INTEGRATIONPOINTS_H
#define INTEGRATIONPOINTS_H


// Contains Nodes of interpolation and their wages for Gauss-Legendre quadratures
// do not modify this file
class IntegrationPoints {
private:
    const Vector<Node> N4{
        Node(-0.57735, -0.57735),   // pc1
        Node(0.57735,-0.57735),   // pc2
        Node(0.57735,0.57735),   // pc3
        Node(-0.57735, 0.57735)
    };
    const Vector<Node> N9{
        Node(-0.7746, -0.7746),
        Node(0, -0.7746),
        Node(0.7746, -0.7746),

        Node(0.7746, 0.0),
        Node(0.0, 0.0),
        Node(-0.7746, 0.0),

        Node(-0.7746, 0.7746),
        Node(0, 0.7746),
        Node(0.7746, 0.7746)
    };
    const Vector<Node> N16{
        Node(-0.861136, -0.861136),
        Node(-0.339981, -0.861136),
        Node(0.339981, -0.861136),
        Node(0.861136, -0.861136),

        Node(0.861136, -0.339981),
        Node(0.339981, -0.339981),
        Node(-0.339981, -0.339981),
        Node(-0.861136, -0.339981),

        Node(-0.861136, 0.339981),
        Node(-0.339981, 0.339981),
        Node(0.339981, 0.339981),
        Node(0.861136, 0.339981),

        Node(0.861136, 0.861136),
        Node(0.339981, 0.861136),
        Node(-0.339981, 0.861136),
        Node(-0.861136, 0.861136),
    };
    const Vector<Node> N25{
        Node(-0.906180, -0.906180),
        Node(-0.538469, -0.906180),
        Node(0, -0.906180),
        Node(0.538469, -0.906180),
        Node(0.906180, -0.906180),

        Node(0.906180, -0.538469),
        Node(0.538469, -0.538469),
        Node(0, -0.538469),
        Node(-0.538469, -0.538469),
        Node(-0.906180, -0.538469),

        Node(-0.906180,0),
        Node(-0.538469, 0),
        Node(0, 0),
        Node(0.538469, 0),
        Node(0.906180, 0),

        Node(0.906180, 0.538469),
        Node(0.538469, 0.538469),
        Node(0, 0.538469),
        Node(-0.538469, 0.538469),
        Node(-0.906180, 0.538469),

        Node(-0.906180, 0.906180),
        Node(-0.538469, 0.906180),
        Node(0, 0.906180),
        Node(0.538469, 0.906180),
        Node(0.906180, 0.906180),
    };
    const Matrix<Vector<double>> constWages = {
        {Vector<double>{1,1}},
        {Vector<double> {5.0/9.0,8.0/9.0, 5.0/9.0}},
        {Vector<double> {0.347855, 0.652145,0.652145,0.347855}},
        {Vector<double> {0.236927, 0.478629,0.568889,0.478629,0.236927}}
    };

    Vector<Node> integrationPoints;
    Vector<double> wages;
public:
    explicit IntegrationPoints(int IPpoints = 4);
    void setIntegrationPoints(int IPpoints);

    [[nodiscard]] Vector<Node> getIP() const;
    [[nodiscard]] Vector<double> getWages() const;
    [[nodiscard]] int getNIP() const;
    static Vector<Node> N4Surface;
};

#endif //INTEGRATIONPOINTS_H
