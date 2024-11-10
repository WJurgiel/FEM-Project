//
// Created by Wojtek on 08.11.2024.
//

#include "IntegrationPoints.h"

IntegrationPoints::IntegrationPoints(int IPpoints) {
    setIntegrationPoints(IPpoints);
}

void IntegrationPoints::setIntegrationPoints(int IPpoints) {
    switch (IPpoints) {
        case 4: integrationPoints = N4; wages = constWages[0][0]; break;
        case 9: integrationPoints = N9; wages = constWages[1][0]; break;
        case 16: integrationPoints = N16; wages = constWages[2][0]; break;
        case 25: integrationPoints = N25; wages = constWages[3][0]; break;
        default: throw std::runtime_error("[ERROR]: Provide valid integration point count next time (4/9/16/25)\n");
    }
}

Vector<Node> IntegrationPoints::getIP() const {
    return integrationPoints;
}

Vector<double> IntegrationPoints::getWages() const {
    return wages;
}
