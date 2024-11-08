#include <iostream>

#include "Includes/Element.h"
#include "Includes/ElemUniv.h"
#include "Includes/Grid.h"
#include "Includes/IntegrationPoints.h"
#include "Includes/Node.h"
int main()
{
    std::string file1 = "../Input/Test1_4_4.txt";
    std::string file2 = "../Input/Test2_4_4_MixGrid.txt";
    std::string file3 = "../Input/Test3_31_31_kwadrat.txt";
    IntegrationPoints ip(25);

    Grid FEM_grid(ip.getIP(), ip.getWages(), file1);
    
    ElemUniv elem_univ(FEM_grid.getIntegrationPoints(), FEM_grid.getNip());

    FEM_grid.executeCalculations(elem_univ.dN_dEta, elem_univ.dn_dKsi);

    std::cout << elem_univ;

    return 0;

}
