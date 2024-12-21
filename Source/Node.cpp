//
// Created by Wojtek on 24.10.2024.
//

#include "Node.h"


Node::Node(double x, double y, bool isBC) {
    this->x = x;
    this->y = y;
    id = -1;
    this->isBC = isBC;
}

Node::Node(int id, double x, double y, bool isBC) {
    this->id = id;
    this->x = x;
    this->y = y;
    this->isBC = isBC;
}

int Node::getID() const {
    return id;
}

double Node::getX() const {
    return x;
}

double Node::getY() const {
    return y;
}

void Node::setBC(bool val) {
    this->isBC = val;
}

bool Node::getBC() const {
    return isBC;
}
