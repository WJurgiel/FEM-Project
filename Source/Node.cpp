//
// Created by Wojtek on 24.10.2024.
//

#include "Node.h"


Node::Node(double x, double y) {
    this->x = x;
    this->y = y;
    id = -1;
}

Node::Node(int id, double x, double y) {
    this->id = id;
    this->x = x;
    this->y = y;
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
