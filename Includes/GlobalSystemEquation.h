//
// Created by Wojtek on 20.11.2024.
//

#ifndef GLOBALSYSTEMEQUATION_H
#define GLOBALSYSTEMEQUATION_H
#include <Element.h>
#include <Grid.h>

#include "Includes.h"


class GlobalSystemEquation {
private:
    Matrix<double> H_global;
    Vector<double> P_global;
    Vector<double> T_vector;
public:
    Matrix<double>& getHGlobalRef() {
        return H_global;
    }
    Vector<double>& getPGlobalRef() {
        return P_global;
    }
    void initializeGlobalMatrixes(int size) {
        H_global = Matrix<double>(size, std::vector<double>(size, 0.0));
        P_global = Vector<double>(size);

    }
    void updateHGlobal(int posX, int posY, double val) {
        H_global[posX][posY] += val;
    }
    void updatePGlobal(int posX, double val) {
        P_global[posX] += val;
    }
    void solveT();
    friend std::ostream& operator<<(std::ostream& os, const GlobalSystemEquation& eqn);
};
// GlobalSystemEquation and Grid must exist, counts the HGlobal in GlobalSystemEquation
inline void aggregation(const Grid& grid, GlobalSystemEquation& eq) {
    // Get Node count to make Hglobal Ncount x Ncount
    int size = grid.getNodes().size();
    if(!size || size == 0) {
        std::cout << "Please create Grid element first";
        return;
    }
    eq.initializeGlobalMatrixes(size);

    //for each element
    for(int i = 0; i < grid.getElementCount(); i++) {
        const Element& currentElem = grid.getElement(i);

        const Matrix<double>& currentHFinal = currentElem.getH_final();
        const Vector<double> currentP = currentElem.getP();
        const Vector<int>& currentNodeIds = currentElem.getNodeIDs();
        // Take local H_local = elem(i).getHFinal
        const Matrix<double>& H_local = currentHFinal;
        const Vector<double>& P_local = currentP;

        // each element has 4 nodes
        for(int rowID = 0; rowID < 4; rowID++) {
            for(int colID = 0; colID < 4; colID++) {
                eq.updateHGlobal(currentNodeIds[rowID],currentNodeIds[colID], H_local[rowID][colID]);
            }
            eq.updatePGlobal(currentNodeIds[rowID],P_local[rowID]);
        }
    }

}
inline Vector<double> gaussElimination(Matrix<double> H, Vector<double> P) {
    int n = H.size();
    Vector t(n, 0.0);

    for (int i = 0; i < n; i++) {
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {
            if (abs(H[k][i]) > abs(H[maxRow][i]))
                maxRow = k;
        }

        std::swap(H[i], H[maxRow]);
        std::swap(P[i], P[maxRow]);

        for (int k = i + 1; k < n; k++) {
            double c = -H[k][i] / H[i][i];
            for (int j = i; j < n; j++) {
                if (i == j) {
                    H[k][j] = 0;
                } else {
                    H[k][j] += c * H[i][j];
                }
            }
            P[k] += c * P[i];
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        t[i] = P[i] / H[i][i];
        for (int k = i - 1; k >= 0; k--) {
            P[k] -= H[k][i] * t[i];
        }
    }

    return t;
}
#endif //GLOBALSYSTEMEQUATION_H
