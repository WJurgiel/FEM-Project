//
// Created by Wojtek on 24.10.2024.
//

#ifndef ELEMUNIV_H
#define ELEMUNIV_H

#include <iomanip>

#include "Includes.h"
#include "Node.h"
class ElemUniv {
public:
    Matrix<double> dN_dEta;
    Matrix<double> dn_dKsi;

    ElemUniv(Vector<Node> integPoints, int npc);

    // need test integration points
    //need nip;
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
