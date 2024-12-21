#include <GlobalSystemEquation.h>
#include <iostream>

#include "ElemUniv.h"
#include "FileHandler.h"
#include "Grid.h"
#include "IntegrationPoints.h"
#include "Timer.h"
#include <thread>
#include <mutex>

std::mutex cout_mutex;
int main()
{
    std::string file1 = "../Input/Test1_4_4.txt";
    std::string file2 = "../Input/Test2_4_4_MixGrid.txt";
    std::string file3 = "../Input/Test3_31_31_kwadrat.txt";
    IntegrationPoints ip(4);
    Timer timer;
    FileHandler::initDirectories();
    ElemUniv elem_univ(ip.getIP(), ip.getNIP());
    Grid FEM_grid(ip.getIP(), ip.getWages(), file1, elem_univ);
    FEM_grid.executeCalculations(elem_univ.getdN_dEta(), elem_univ.getdN_dKsi());

    //-----test start----
    // ElemUniv testElemUniv(ip.getIP(), ip.getNIP());
    // Grid testGrid(ip.getIP(), ip.getWages(), testElemUniv);
    // testGrid.executeCalculations(testElemUniv.getdN_dEta(), testElemUniv.getdN_dKsi());
    // std::cout << testGrid;
    // -----test end-----

#if CALCULATIONS
    int elCount = FEM_grid.getElementCount();
    Vector<std::thread> threads;
    FileHandler::clearOutputDirectory();
    FileHandler::initDirectories();
    timer.start();
#if MULTITHREADING
    {
        for(int pid = 0; pid < elCount; pid++) {
            threads.emplace_back([&FEM_grid, &elem_univ, pid]() {
                FEM_grid.executeCalculations(
                    elem_univ.getdN_dEta(),
                    elem_univ.getdN_dKsi(),
                    pid
                    );
            });
        }
        for(int pid = 0; pid < elCount; pid++) {
            threads[pid].join();
        }
    }
#endif
#if MULTITHREADING
    FEM_grid.executeCalculations(elem_univ.getdN_dEta(), elem_univ.getdN_dKsi());
#endif
    timer.stop();
#endif

    GlobalSystemEquation globalSystemEquation;
    // std::cout << FEM_grid;
    // //Uncomment code below to call aggregation
    aggregation(FEM_grid, globalSystemEquation);
    std::cout<<globalSystemEquation;
    // globalSystemEquation.solveT();
    std::cout << timer;
    return 0;

}
