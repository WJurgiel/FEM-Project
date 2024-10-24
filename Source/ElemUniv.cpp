//
// Created by Wojtek on 24.10.2024.
//

#include "../Includes/ElemUniv.h"

ElemUniv::ElemUniv(Vector<Node> integPoints, int nip) {
    dN_dEta.resize(nip, std::vector<double>(4)); // 4 columns because you're accessing dN_dEta[ip][0] to dN_dEta[ip][3]
    dn_dKsi.resize(nip, std::vector<double>(4));

    for(auto ip = 0; ip < nip; ip++) { // ip - integration point
        dN_dEta[ip][0] = -0.25 * (1 - integPoints[ip].y);
        dN_dEta[ip][1] = 0.25 * (1 - integPoints[ip].y);
        dN_dEta[ip][2] = 0.25 * (1 + integPoints[ip].y);
        dN_dEta[ip][3] = -0.25 * (1 + integPoints[ip].y);

        dn_dKsi[ip][0] = -0.25 * (1 - integPoints[ip].x);
        dn_dKsi[ip][1] = -0.25 * (1 + integPoints[ip].x);
        dn_dKsi[ip][2] = 0.25 * (1 + integPoints[ip].x);
        dn_dKsi[ip][3] = 0.25 * (1 - integPoints[ip].x);
    }

}
