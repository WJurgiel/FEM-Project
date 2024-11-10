//
// Created by Wojtek on 24.10.2024.
//

#include "Grid.h"

#include <filesystem>

void Grid::clearFile(std::string out_file_name) {
    std::ofstream outFile(out_file_name, std::ios::out);
    try {
        if(outFile.is_open()) {
            outFile << "";
#if DEBUG
            std::cout << out_file_name << " cleared successfully\n";
        }
        else {
            std::cerr << "Error opening file " << out_file_name << std::endl;
#endif
        }


    }catch(std::exception& e){
        std::cout << e.what() << "\n";
    }
    outFile.close();
}

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
    for(const auto& entry: std::filesystem::directory_iterator("../Output/")) {
        std::filesystem::remove_all(entry.path());
    }
    std::filesystem::create_directory("../Output/Jacobian_Matrices");
    std::filesystem::create_directory("../Output/Hpc");
    std::filesystem::create_directory("../Output/H_final");
#if DEBUG
    std::cout << "Grid::executeCalculations() logs\n";
#endif
    Grid::clearFile("../Output/dNdXdY.txt");
    for(int elem = 0; elem < elements.size(); ++elem) {
        //calculations

        elements[elem].calculateJacobians(nip, dN_dEta, dN_dKsi, elements[elem].getNodes() );
        elements[elem].calculate_dN_dx_dy(nip, dN_dEta, dN_dKsi);
        elements[elem].calculate_H_matrix(nip, globalData.getParameter("Conductivity"));
        elements[elem].calculate_H_final(nip, this->wages);
        //output to file
#if DEBUG
        std::cout << "[---Element "  << elem << "---]\n";
#endif
        Grid::clearFile("../Output/Jacobian_Matrices/jac_matrix_elem_" + std::to_string(elem)+".txt");
        elements[elem].printJacobians(nip, "../Output/Jacobian_Matrices/jac_matrix_elem_" + std::to_string(elem)+".txt");
        elements[elem].printMatrix(elements[elem].getdN_dx(), "../Output/dNdXdY.txt", "dN/dx");
        elements[elem].printMatrix(elements[elem].getdN_dy(), "../Output/dNdXdY.txt", "dN/dy");

        for(int ip = 0; ip < nip; ip++) {
            std::string matrixName = "H" + std::to_string(ip);
            std::string fileName = "../Output/Hpc/Hpc_elem_" + std::to_string(elem) + ".txt";
            if(ip == 0) Grid::clearFile(fileName);
            elements[elem].printMatrix(elements[elem].getH_matrixes(ip), fileName, matrixName);
        }
        Grid::clearFile("../Output/H_final/H_elem_" + std::to_string(elem) + ".txt");
        elements[elem].printMatrix(elements[elem].getH_final(), "../Output/H_final/H_elem_" + std::to_string(elem) + ".txt", "H");
    }
}

Grid::Grid(Vector<Node> integrationPoints,Vector<double> wages) {
    //test constructor
    nodes.emplace_back(0, 0,0);
    nodes.emplace_back(1, 0.025,0);
    nodes.emplace_back(2, 0.025,0.025);
    nodes.emplace_back(3, 0,0.025);
    // Dla testu 2
    // nodes.emplace_back(0, 0.01,-0.01);
    // nodes.emplace_back(1, 0.025,0);
    // nodes.emplace_back(2, 0.025,0.025);
    // nodes.emplace_back(3, 0,0.025);

    elements.push_back(Element(0,{0,1,2,3}));

    this->integrationPoints = integrationPoints;

    globalData.setParameter("Conductivity",30);

    this->wages = wages;
    nip = static_cast<int>(this->integrationPoints.size());

    assignNodesToElements();
}

Grid::Grid(Vector<Node> integrationPoints, Vector<double> wages,std::string fileName, int normalize) {
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
            // if (isBC) {
            //     std::stringstream ss(line);
            //     int bcVal;
            //     char comma;
            //     while (ss >> bcVal) {
            //         bc.push_back(bcVal);
            //         ss >> comma;
            //     }
            // }
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

