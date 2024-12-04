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
public:
    Matrix<double>& getHGlobalRef() {
        return H_global;
    }
    void initializeHGlobal(int size) {
        H_global = Matrix<double>(size, std::vector<double>(size, 0.0));
        std::cout << "Initialized: \n" << *this;
    }
    void updateHGlobal(int posX, int posY, double val) {
        H_global[posX][posY] += val;
    }
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
    eq.initializeHGlobal(size);

    //for each element
    for(int i = 0; i < grid.getElementCount(); i++) {
        const Element& currentElem = grid.getElement(i);
        const Matrix<double>& currentHFinal = currentElem.getH_final();
        const Vector<int>& currentNodeIds = currentElem.getNodeIDs();
        // Take local H_local = elem(i).getHFinal
        const Matrix<double>& H_local = currentHFinal;

        // each element has 4 nodes
        for(int rowID = 0; rowID < 4; rowID++) {
            for(int colID = 0; colID < 4; colID++) {
                eq.updateHGlobal(currentNodeIds[rowID],currentNodeIds[colID], H_local[rowID][colID]);
            }
        }
    }

}
#endif //GLOBALSYSTEMEQUATION_H
