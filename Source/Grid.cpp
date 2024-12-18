//
// Created by Wojtek on 24.10.2024.
//

#include "Grid.h"

#include <filesystem>
#include "FileHandler.h"
void Grid::assignNodesToElements() {
    for(int elem = 0; elem < elements.size(); ++elem) {
        Vector<Node> newNodes;
        for(int id = 0; id < elements[elem].getNodeIDs().size(); ++id) {
            newNodes.push_back(nodes[elements[elem].getNodeIDs()[id]]);
        }
        elements[elem].setNodes(newNodes);
    }
}

void Grid::executeCalculations(Matrix<double>& dN_dEta, Matrix<double>& dN_dKsi) {


    std::cout << "nip: " << nip << "\n";
    FileHandler::clearOutputDirectory();
    FileHandler::initDirectories();
#if DEBUGINFO
    std::cout << "Grid::executeCalculations() logs\n";
#endif
    FileHandler::clearFile("../Output/dNdXdY.txt"); // think about where to store paths
    //calculations and saving
    for(int elem = 0; elem < elements.size(); ++elem) {
        elements[elem].calculateJacobians(nip, dN_dEta, dN_dKsi, elements[elem].getNodes());
        elements[elem].calculate_dN_dx_dy(nip, dN_dEta, dN_dKsi);
        elements[elem].calculate_H_matrix(nip, globalData.getParameter("Conductivity"));
        elements[elem].calculate_HBC_matrix(nip, globalData.getParameter("Conductivity"), m_elem_univ);
        elements[elem].calculate_H_final(nip, this->wages);
#if DEBUGINFO
        std::cout << "[---Element "  << elem << "---]\n";
#endif
        std::string jac_path = "../Output/Jacobian_Matrices/jac_matrix_elem_" + std::to_string(elem) + ".txt";
        std::string dNdXdY_path = "../Output/dNdXdY.txt";
        std::string H_final_path = "../Output/H_final/H_elem_" + std::to_string(elem) + ".txt";
        std::string Hpc_path = "../Output/Hpc/Hpc_elem_" + std::to_string(elem) + ".txt";

        // Jacobian matrices output
        FileHandler::saveToFile(jac_path, elements[elem], elements[elem].getJacobianConstantsMatrixes(), nip);

        // dNdXdY output
        FileHandler::saveToFile(dNdXdY_path, elements[elem], elements[elem].getdN_dx(), "dN/dx", nip, false);
        FileHandler::saveToFile(dNdXdY_path, elements[elem], elements[elem].getdN_dy(), "dN/dx", nip, false);

        // Hpc matrices output
        for (int ip = 0; ip < nip; ip++) {
            std::string matrixName = "H" + std::to_string(ip);
            if (ip == 0) FileHandler::clearFile(Hpc_path); // delete only on start for this element
            FileHandler::saveToFile(Hpc_path, elements[elem], elements[elem].getH_matrixes(ip), matrixName, nip, false);
        }

        // H final output
        FileHandler::saveToFile(H_final_path, elements[elem], elements[elem].getH_final(), "H", nip);
    }
}
/* To make it work as it should, call
 * FileHandler::clearOutputDirectory()
 * FileHandler::initDirectories()
 right before calling, otherwise you will receive just one file
 */
void Grid::executeCalculations(Matrix<double> & dN_dEta, Matrix<double> &dN_dKsi, int elementID) {
    // FileHandler::clearOutputDirectory();
    // FileHandler::initDirectories();
#if DEBUGINFO
    std::cout << "Grid::executeCalculations() logs\n";
#endif
    FileHandler::clearFile("../Output/dNdXdY.txt"); // think about where to store paths
    //calculations and saving
    elements[elementID].calculateJacobians(nip, dN_dEta, dN_dKsi, elements[elementID].getNodes());
    elements[elementID].calculate_dN_dx_dy(nip, dN_dEta, dN_dKsi);
    elements[elementID].calculate_H_matrix(nip, globalData.getParameter("Conductivity"));
    elements[elementID].calculate_H_final(nip, this->wages);

#if DEBUGINFO
        std::cout << "[---Element "  << elem << "---]\n";
#endif
        std::string jac_path = "../Output/Jacobian_Matrices/jac_matrix_elem_" + std::to_string(elementID) + ".txt";
        std::string dNdXdY_path = "../Output/dNdXdY.txt";
        std::string H_final_path = "../Output/H_final/H_elem_" + std::to_string(elementID) + ".txt";
        std::string Hpc_path = "../Output/Hpc/Hpc_elem_" + std::to_string(elementID) + ".txt";

        // Jacobian matrices output
        FileHandler::saveToFile(jac_path, elements[elementID], elements[elementID].getJacobianConstantsMatrixes(), nip);

        // dNdXdY output
        FileHandler::saveToFile(dNdXdY_path, elements[elementID], elements[elementID].getdN_dx(), "dN/dx", nip, false);
        FileHandler::saveToFile(dNdXdY_path, elements[elementID], elements[elementID].getdN_dy(), "dN/dx", nip, false);

        // Hpc matrices output
        for (int ip = 0; ip < nip; ip++) {
            std::string matrixName = "H" + std::to_string(ip);
            if (ip == 0) FileHandler::clearFile(Hpc_path); // delete only on start for this element
            FileHandler::saveToFile(Hpc_path, elements[elementID], elements[elementID].getH_matrixes(ip), matrixName, nip, false);
        }

        // H final output
        FileHandler::saveToFile(H_final_path, elements[elementID], elements[elementID].getH_final(), "H", nip);

}

Grid::Grid(Vector<Node> integrationPoints,Vector<double> wages, ElemUniv& elem_univ): m_elem_univ(elem_univ) {
    //test constructor
    nodes.emplace_back(0, 0, 0, true);
    nodes.emplace_back(1, 0.025, 0, true);
    nodes.emplace_back(2, 0.025, 0.025, true);
    nodes.emplace_back(3, 0, 0.025, true);
    // Dla testu 2
    // nodes.emplace_back(0, 0.01,-0.01);
    // nodes.emplace_back(1, 0.025,0);
    // nodes.emplace_back(2, 0.025,0.025);
    // nodes.emplace_back(3, 0,0.025);
    globalData.setParameter("Conductivity", 25);
    elements.push_back(Element(0, {0, 1, 2, 3}));

    this->integrationPoints = integrationPoints;



    this->wages = wages;
    nip = static_cast<int>(this->integrationPoints.size());

    assignNodesToElements();
}

Grid::Grid(Vector<Node> integrationPoints, Vector<double> wages,std::string fileName,ElemUniv& elem_univ, int normalize):m_elem_univ(elem_univ) {
    //configure integration points
    this->integrationPoints = integrationPoints;
    this->wages = wages;
    nip = static_cast<int>(this->integrationPoints.size());

    //Read from file
    try {
        File file;
        file.open(fileName);

        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + fileName);
        }

        bool isNodeSection = false;
        bool isElementSection = false;
        bool isBC = false;
        std::string line;
        while(std::getline(file,line)) {
            Vector<std::string> tokens = split(line, ' ');
            if(tokens.empty()) continue;

            if (tokens[0] == "*Node") {
                isNodeSection = true;
                isElementSection = false;
                isBC = false;
                continue;
            }
            if (tokens[0] == "*Element,") {
                isNodeSection = false;
                isElementSection = true;
                isBC = false;
                continue;
            }
            if (tokens[0] == "*BC") {
                isNodeSection = false;
                isElementSection = false;
                isBC = true;
            }
            if (isNodeSection) {
                std::stringstream ss(line);
                double x, y;
                char other;
                int index;
                ss >> index >> other >> x >>other >> y; //check if it does it correctly
                nodes.push_back(Node{index-normalize,x,y});
            }
            if (isElementSection) {
                std::stringstream ss(line);
                std::vector<int> elems = std::vector<int>(5, 0);
                char comma;
                ss >> elems[0] >> comma >> elems[1] >> comma >> elems[2] >> comma >> elems[3] >> comma >> elems[4];

                elements.push_back(Element{elems[0]-normalize, Vector<int>{elems[1]-normalize,elems[2]-normalize,elems[3]-normalize,elems[4]-normalize}});
            }
            if (isBC) {
                std::stringstream ss(line);
                int bcVal;
                char comma;
                while (ss >> bcVal) {
                    nodes[bcVal - normalize].setBC(true);
                    ss >> comma;
                }
            }
            if (!isNodeSection && !isElementSection && !isBC) {
                int value = std::stoi(tokens[1]);
                globalData.setParameter(tokens[0], value);
            }
        }
        file.close();

    }catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    //configure Elements
    try {
        assignNodesToElements();
    }catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }

}

int Grid::getNip() const {
    return nip;
}

Vector<Node> Grid::getIntegrationPoints() const {
    return integrationPoints;
}

std::size_t Grid::getElementCount() const {
    return elements.size();
}

Element Grid::getElement(int id) const {
    return elements[id];
}

Vector<Node> Grid::getNodes() const {
    return nodes;
}

