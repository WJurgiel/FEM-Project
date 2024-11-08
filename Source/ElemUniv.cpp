//
// Created by Wojtek on 24.10.2024.
//

#include "../Includes/ElemUniv.h"

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

}

Matrix<double> & ElemUniv::getdN_dEta()  {
    return dN_dEta;
}

Matrix<double> & ElemUniv::getdN_dKsi() {
    return dn_dKsi;
}
