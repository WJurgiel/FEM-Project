//
// Created by Wojtek on 19.10.2024.
//

#ifndef JACOBIMETHOD_H
#define JACOBIMETHOD_H
#include "Includes.h"

#define ETA 0 // eta is local X
#define KSI 1   //ksi is local Y
#define X 0
#define Y 1
class JacobiMethod {
    //What to do?
    /*
     *  get nodes vector
     *  count dNi/dEta and dNi/dKsi
     *  count Jacobi matrix
     *  count det[Jac]
     */
private:
    int npc; // number of integration points
    double determinant;
    Matrix exampleData = {{0,0},{0.025,0},{0.025,0.025}, {0,0.025}};
    Matrix dn_i_dEta;// row - integPoint / dEta column: N1,N2,N3,N4/dEta
    Matrix dn_i_dKsi;
    Matrix jacobian = {{0,0},{0,0}};
    Matrix jacobian1;
    Matrix integrationPoints;

    void populateDnEta(Matrix& dn_i_dEta, Matrix integPoints) const;     // calculates dn_i_matrix
    void populateDnKsi(Matrix &dn_i_dKsi, Matrix integPoints) const;
    void populateJacobiMatrix( Matrix& jacobian);// calculates dn_i_matrix
    double calculateDetJacobi(Matrix& jacobian);    // returns det[J] NOT THE REVERSED VARIANT
    void populateJacobi1();
public:
    explicit JacobiMethod(Matrix integrationPoints);

    void executeJacobiMethod();
    void getOutput() const;
    Matrix getJacobiMatrix() const;
    Matrix getJacobiMatrix1() const;
    double getJacobiDeterminant() const;

};



#endif //JACOBIMETHOD_H
