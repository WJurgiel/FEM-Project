#include <iostream>

#include "ElemUniv.h"
#include "FileHandler.h"
#include "Grid.h"
#include "IntegrationPoints.h"
#include "Timer.h"
int main()
{
    std::string file1 = "../Input/Test1_4_4.txt";
    std::string file2 = "../Input/Test2_4_4_MixGrid.txt";
    std::string file3 = "../Input/Test3_31_31_kwadrat.txt";
    IntegrationPoints ip(4);
    Timer timer;
    FileHandler::initDirectories();
    Grid FEM_grid(ip.getIP(), ip.getWages(), file1);
    
    ElemUniv elem_univ(FEM_grid.getIntegrationPoints(), FEM_grid.getNip());

    timer.start();
    FEM_grid.executeCalculations(elem_univ.getdN_dEta(), elem_univ.getdN_dKsi());
    timer.stop();

    std::cout << elem_univ;
    std::cout << timer;
    return 0;

}
