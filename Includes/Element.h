//
// Created by Wojtek on 24.10.2024.
//

#ifndef ELEMENT_H
#define ELEMENT_H

#include "Includes.h"
#include "Jacobian.h"
#include "Node.h"

// The encapsulation problem will be potentially solved soon...
class Element {
    int id;
    Vector<int> nodeIDs;
    Vector<Node> nodes;
    Vector<Jacobian> jacobianConstantsMatrixes; // each jacobian matrix for each of the integration points
    Matrix<double> dN_dx;
    Matrix<double> dN_dy;
    Vector<Matrix<double>> H_matrixes; // contains H_matrix for each of integration points
    Matrix<double> H_final;
public:
    Element(int id, Vector<int> nodeIDs);

    void calculateJacobians(int nip, Matrix<double> dN_dEta, Matrix<double> dN_dKsi,  Vector<Node> elemNodes);
    void calculate_dN_dx_dy(int npc, Matrix<double> dN_dEta, Matrix<double> dN_dKsi);
    void calculate_H_matrix(int nip,double conductivity);
    void calculate_H_final(int nip, Vector<double> wages);

    void printJacobians(int nip) const;
    void printMatrix(Matrix<double>);
    //Getters
    Vector<int> getNodeIDs()const ;
    Vector<Node> getNodes() const;
    Matrix<double> getdN_dx() const;
    Matrix<double> getdN_dy() const;
    Matrix<double> getH_matrixes(int ip) const;
    Vector<Jacobian> getJacobianConstantsMatrixes() const;
    Vector<Matrix<double>> getH_matrixes() const;
    Matrix<double> getH_final() const;
    int getID() const;

    //Setters
    void setNodes(Vector<Node>);
    friend std::ostream& operator<<(std::ostream& os, const Element& e);

};
inline std::ostream& operator<<(std::ostream& os, const Element& e) {
    os << "Element [" << e.id << "]: ";
    for(auto &n : e.nodeIDs) {
        os << n << " ";
    }
    std::cout << "contains nodes:\n";
    for(auto &n : e.nodes) {
        os << n << " ";
    }
    os << "\n";
    return os;
}



#endif //ELEMENT_H
