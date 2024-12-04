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
    Grid FEM_grid(ip.getIP(), ip.getWages(), file1);
    
    ElemUniv elem_univ(FEM_grid.getIntegrationPoints(), FEM_grid.getNip());

    int elCount = FEM_grid.getElementCount();
    Vector<std::thread> threads;
    FileHandler::clearOutputDirectory();
    FileHandler::initDirectories();
    timer.start();
    {
        for(int pid = 0; pid < elCount; pid++) {
            threads.emplace_back([&FEM_grid, &elem_univ, pid]() {
                // {
                //     std::lock_guard<std::mutex> guard(cout_mutex);
                //     std::cout << "[THREAD " <<pid << " ]" << "performing task for element: " << pid << "\n";
                // }

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
    // FEM_grid.executeCalculations(elem_univ.getdN_dEta(), elem_univ.getdN_dKsi());
    timer.stop();

    GlobalSystemEquation globalSystemEquation;
    std::cout << FEM_grid;
    aggregation(FEM_grid, globalSystemEquation);
    std::cout << globalSystemEquation;

    std::cout << elem_univ;
    std::cout << timer;
    return 0;

}
