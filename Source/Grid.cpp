//
// Created by Wojtek on 24.10.2024.
//

#include "../Includes/Grid.h"

void Grid::assignNodesToElements() {
    for(int elem = 0; elem < elements.size(); ++elem) {
        Vector<Node> newNodes;
        for(int id = 0; id < elements[elem].getNodeIDs().size(); ++id) {
            newNodes.push_back(nodes[elements[elem].getNodeIDs()[id]]);
        }
        elements[elem].setNodes(newNodes);
    }
}

Grid::Grid(Vector<Node> integrationPoints, std::string fileName, int normalize) {
    //configure integration points
    this->integrationPoints = integrationPoints;
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
