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
    Grid FEM_grid(ip.getIP(), ip.getWages(), file3, elem_univ);

#if CALCULATIONS
    int elCount = FEM_grid.getElementCount();
    std::cout << "DEBUG: " << elCount << " \n";
    Vector<std::thread> threads;
    FileHandler::clearOutputDirectory();
    FileHandler::initDirectories();
    timer.start();
#if MULTITHREADING
    {
#pragma omp parallel for
        for(int pid = 0; pid < elCount; pid++) {
            cout_mutex.lock();
            threads.emplace_back([&FEM_grid, &elem_univ, pid]() {
                FEM_grid.executeCalculations(
                    elem_univ.getdN_dEta(),
                    elem_univ.getdN_dKsi(),
                    pid
                    );
            });
            cout_mutex.unlock();
        }
        for(int pid = 0; pid < elCount; pid++) {
            threads[pid].join();
        }
    }
#else
    FEM_grid.executeCalculations(elem_univ.getdN_dEta(), elem_univ.getdN_dKsi());
#endif
    timer.stop();
#endif

    GlobalSystemEquation globalSystemEquation;
    aggregation(FEM_grid, globalSystemEquation);
    // std::cout<<globalSystemEquation;

    globalSystemEquation.solveSimulation(FEM_grid);
    std::cout << timer;

    return 0;

}
