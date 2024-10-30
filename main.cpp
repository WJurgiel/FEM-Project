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
    const Vector<Node> test_integrationPoints2{
        Node(-0.7746, -0.7746),
        Node(0, -0.7746),
        Node(0.7746, -0.7746),

        Node(0.7746, 0.0),
        Node(0.0, 0.0),
        Node(-0.7746, 0.0),

        Node(-0.7746, 0.7746),
       Node(0, 0.7746),
       Node(0.7746, 0.7746)
    };
    const Matrix<Vector<double>> wages{
        {Vector<double>{1,1}},
        {Vector<double>{5.0/9.0,8.0/9.0, 5.0/9.0}}
    };
    // Grid test_grid(test_integrationPoints, wages[0][0], "../Input/Test1_4_4.txt");
    Grid test_grid(test_integrationPoints2, wages[1][0]);
    std::cout << test_grid << std::endl;

    ElemUniv elem_univ(test_grid.integrationPoints, test_grid.nip);

    std::cout << test_grid;
    test_grid.executeCalculations(elem_univ.dN_dEta, elem_univ.dn_dKsi);

    std::cout << elem_univ; // why is this reversed for 3 point integration
    // somehow it manages to not work XD

    return 0;

}
