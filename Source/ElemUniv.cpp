//
// Created by Wojtek on 24.10.2024.
//

#include "ElemUniv.h"
const Vector<Node> N4Surface = {
    // BOTTOM
    Node(0.57735, 1), //Pc20
    Node(-0.57735,1), //Pc21
    // RIGHT
    Node(-1,0.57735),   //Pc30
    Node(-1,-0.57735),  //Pc31
    //TOP
    Node(-0.57735, -1),   // Pc00
    Node(0.57735,-1),
    //LEFT
    Node(1,-0.57735),   //Pc10
    Node(1,0.57735)
};
const Vector<Node> N9Surface = {
    //BOTTOM
    Node(0.7746, 1),
    Node(0,1),
    Node(-0.7746, 1),
    //RIGHT
    Node(-1, 0.7746),
    Node(-1, 0),
    Node(-1,-0.7746),
    //TOP
    Node(-0.7746, -1),
    Node(0,-1),
    Node(0.7746, -1),
    //LEFT
    Node(1,-0.7746),
    Node(1,0),
    Node(1,0.7746)
};
const Vector<Node> N16Surface = {
    //BOTTOM
    Node(0.861136, 1),
    Node(0.339981, 1),
    Node(-0.339981, 1),
    Node(-0.861136, 1),
    //RIGHT
    Node(-1, 0.861136),
    Node(-1, 0.339981),
    Node(-1, -0.339981),
    Node(-1, -0.861136),
    //TOP
    Node(-0.861136, -1),
    Node(-0.339981, -1),
    Node(0.339981, -1),
    Node(0.861136, -1),
    //LEFT
    Node(1, -0.861136),
    Node(1, -0.339981),
    Node(1, 0.339981),
    Node(1, 0.861136)
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
        surfaces[BOTTOM].surfaceIntegPoints = Vector<Node>{NxSurface[0], NxSurface[1]};
        surfaces[RIGHT].surfaceIntegPoints = Vector<Node>{NxSurface[2], NxSurface[3]};
        surfaces[TOP].surfaceIntegPoints = Vector<Node>{NxSurface[4], NxSurface[5]};
        surfaces[LEFT].surfaceIntegPoints = Vector<Node>{NxSurface[6], NxSurface[7]};
    }
    else if(nip == 9) {
        NxSurface  = N9Surface;
        surfaces[BOTTOM].surfaceIntegPoints = Vector<Node>{NxSurface[0], NxSurface[1], NxSurface[2]};
        surfaces[RIGHT].surfaceIntegPoints = Vector<Node>{NxSurface[3],NxSurface[4], NxSurface[5]};
        surfaces[TOP].surfaceIntegPoints = Vector<Node>{NxSurface[6], NxSurface[7], NxSurface[8]};
        surfaces[LEFT].surfaceIntegPoints = Vector<Node>{NxSurface[9], NxSurface[10], NxSurface[11]};
    }
    else if(nip == 16) {
        NxSurface  = N16Surface;
        surfaces[BOTTOM].surfaceIntegPoints = Vector<Node>{NxSurface[0], NxSurface[1], NxSurface[2], NxSurface[3]};
        surfaces[RIGHT].surfaceIntegPoints = Vector<Node>{NxSurface[4], NxSurface[5], NxSurface[6], NxSurface[7]};
        surfaces[TOP].surfaceIntegPoints = Vector<Node>{NxSurface[8], NxSurface[9], NxSurface[10], NxSurface[11]};
        surfaces[LEFT].surfaceIntegPoints = Vector<Node>{NxSurface[12], NxSurface[13], NxSurface[14], NxSurface[15]};
    }

}

Matrix<double> & ElemUniv::getdN_dEta()  {
    return dN_dEta;
}

Matrix<double> & ElemUniv::getdN_dKsi() {
    return dn_dKsi;
}
