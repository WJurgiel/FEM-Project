#include <iostream>

#include "Includes/Element.h"
#include "Includes/ElemUniv.h"
#include "Includes/Grid.h"
#include "Includes/Node.h"

int main()
{
    Vector<Node> test_nodes;
    test_nodes.emplace_back(0, 0,0);
    test_nodes.emplace_back(1, 0.025,0);
    test_nodes.emplace_back(2, 0.025,0.025);
    test_nodes.emplace_back(3, 0,0.025);

    Element test_element = Element(0, {0,1,2,3});

    GlobalData test_global_data;
    test_global_data.setParameter("Conductivity", 30);

    const Vector<Node> test_integrationPoints{
        Node(-0.57735, -0.57735),   // pc1
        Node(0.57735,-0.57735),   // pc2
        Node(0.57735,0.57735),   // pc3
        Node(-0.57735, 0.57735) // pc4
    };
    Grid test_grid(test_integrationPoints);
    test_grid.elements.emplace_back(test_element);
    test_grid.nodes = test_nodes;
    test_grid.globalData = test_global_data;

    ElemUniv elem_univ(test_grid.integrationPoints, test_grid.nip);
    std::cout << elem_univ;

    //Will be packed up later on...
    //Create Jacobian Matrixes for each of integration points in element[0] and print them
    test_grid.elements[0].calculateJacobians(4, elem_univ.dN_dEta, elem_univ.dn_dKsi, test_grid.nodes);
    test_grid.elements[0].printJacobians(4);
    test_grid.elements[0].calculate_dN_dx_dy(4, elem_univ.dN_dEta,elem_univ.dn_dKsi);
    std::cout << "dN/dX\n";
    test_grid.elements[0].printMatrix(test_grid.elements[0].dN_dx);
    std::cout << "dN/dY\n";
    test_grid.elements[0].printMatrix(test_grid.elements[0].dN_dy);


    Vector<double> derivatives; // it is required, will probably just make the same vector in Element so it doesn't have to be passed
    for(int ip = 0; ip < 4; ip++)
        derivatives.push_back(test_grid.elements[0].jacobianConstantsMatrixes[ip].getDeterminant());

    test_grid.elements[0].calculate_H_matrix(4, test_grid.globalData.getParameter("Conductivity"), derivatives);
    for(int ip = 0; ip < 4; ip++) {
        std::cout << "H[" << ip << "]:\n";
        test_grid.elements[0].printMatrix(test_grid.elements[0].H_matrixes[ip]);
    }

    std::cout << "Final H:\n";
    test_grid.elements[0].calculate_H_final(4, {1,1});
    test_grid.elements[0].printMatrix(test_grid.elements[0].H_final);

    return 0;

}
