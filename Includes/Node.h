//
// Created by Wojtek on 24.10.2024.
//

#ifndef NODE_H
#define NODE_H

#include "Includes.h"

class Node {
public:
    int id;
    double x,y;

    Node(double x, double y);
    Node(int id, double x, double y);

    friend std::ostream& operator<<(std::ostream& os, const Node& n);
};
inline std::ostream& operator<<(std::ostream& os, const Node& n) {
    os << "[" << n.id << "]: (" << n.x << ", " << n.y << ")\n";
    return os;
}
// After assuring that the calculations work fine, add methods to read from file
#endif //NODE_H
