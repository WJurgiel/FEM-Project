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

    // std::cout << test_grid;
    return 0;

}
