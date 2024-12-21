//
// Created by Wojtek on 24.10.2024.
//

#ifndef ELEMUNIV_H
#define ELEMUNIV_H

#include <cmath>
#include <IntegrationPoints.h>
#include <iomanip>

#include "Includes.h"
#include "Node.h"
//Surfaces correct with convention: reverse clockwise
enum Surfaces {
    BOTTOM,
    RIGHT,
    TOP,
    LEFT
};
class ElemUniv {
private:
    Matrix<double> dN_dEta;
    Matrix<double> dn_dKsi;
    int nip;
public:
    ElemUniv(Vector<Node> integPoints, int nip);

    //Getters
    Matrix<double> & getdN_dEta();
    Matrix<double> & getdN_dKsi();

    struct Surface {
        // [INITIALIZED] contains the integration points on the surface (IntegrationPoints::NxSurface
        Vector<Node> surfaceIntegPoints;
        // [UNITIALIZED ON START] [sqrt(npc) x 4]
        Matrix<double> N;
        double surfaceLength;
    };
    Surface surfaces[4];

    friend std::ostream& operator<<(std::ostream& os, const ElemUniv& elemUniv);
};
inline std::ostream& operator<<(std::ostream& os, const ElemUniv& elemUniv) {
   os << std::setw(10) << "pc/\tdN0_d/Eta\tdN1_d/Eta\tdN2_d/Eta\tdN3_d/Eta\n";
   os << "----------------------------------------------------------------\n";
    os << "dN_dEta:\n";
   for (auto& x: elemUniv.dN_dEta) {
       for (auto& y: x) {
            os<< y  << std::setw(10)<< "\t";
       }
       std::cout << "\n";
   }
    std:: cout << "\n";
   os << std::setw(10) << "pc/\tdN0_d/Ksi\tdN1_d/Ksi\tdN2_d/Ksi\tdN3_d/Ksi\n";
   os << "-----------------------------------------------------------------\n";
    os << "dN_dKsi:\n";
    for (auto& x: elemUniv.dn_dKsi) {
        for (auto& y: x) {
            os<< y  << std::setw(10)<< "\t";
        }
        os << "\n";
    }
    return os;
}




#endif //ELEMUNIV_H
