//
// Created by Wojtek on 24.10.2024.
//

#include "ElemUniv.h"
Vector<Node> N4Surface = {
    //TOP
    Node(0.57735, 1), //Pc20
    Node(-0.57735,1), //Pc21
    //LEFT
    Node(-1,0.57735),   //Pc30
    Node(-1,-0.57735),  //Pc31
    // BOTTOM
    Node(-0.57735, -1),   // Pc00
    Node(0.57735,-1),   // Pc01
    // RIGHT
    Node(1,-0.57735),   //Pc10
    Node(1,0.57735),   //Pc11

};
ElemUniv::ElemUniv(Vector<Node> integPoints, int nip) {
    dN_dEta.resize(nip, std::vector<double>(4)); // 4 columns because you're accessing dN_dEta[ip][0] to dN_dEta[ip][3]
    dn_dKsi.resize(nip, std::vector<double>(4));

    for(auto ip = 0; ip < nip; ip++) { // ip - integration point
        dN_dEta[ip][0] = -0.25 * (1 - integPoints[ip].getY());
        dN_dEta[ip][1] = 0.25 * (1 - integPoints[ip].getY());
        dN_dEta[ip][2] = 0.25 * (1 + integPoints[ip].getY());
        dN_dEta[ip][3] = -0.25 * (1 + integPoints[ip].getY());

        dn_dKsi[ip][0] = -0.25 * (1 - integPoints[ip].getX());
        dn_dKsi[ip][1] = -0.25 * (1 + integPoints[ip].getX());
        dn_dKsi[ip][2] = 0.25 * (1 + integPoints[ip].getX());
        dn_dKsi[ip][3] = 0.25 * (1 - integPoints[ip].getX());
    }

    // calculate the Surface boundary conditions
    Vector<Node> NxSurface;
    if(nip == 4) {
        NxSurface  = N4Surface;
    }
    surfaces[TOP].surfaceIntegPoints = Vector<Node>{NxSurface[0], NxSurface[1]};
    surfaces[LEFT].surfaceIntegPoints = Vector<Node>{NxSurface[2], NxSurface[3]};
    surfaces[BOTTOM].surfaceIntegPoints = Vector<Node>{NxSurface[4], NxSurface[5]};
    surfaces[RIGHT].surfaceIntegPoints = Vector<Node>{NxSurface[6], NxSurface[7]};
}

Matrix<double> & ElemUniv::getdN_dEta()  {
    return dN_dEta;
}

Matrix<double> & ElemUniv::getdN_dKsi() {
    return dn_dKsi;
}
