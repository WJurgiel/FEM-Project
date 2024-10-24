//
// Created by Wojtek on 24.10.2024.
//

#include "../Includes/Grid.h"
Grid::Grid(Vector<Node> integrationPoints) {
    this->integrationPoints = integrationPoints;
    nip = static_cast<int>(this->integrationPoints.size());
}