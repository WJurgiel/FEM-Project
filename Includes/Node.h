//
// Created by Wojtek on 24.10.2024.
//

#ifndef NODE_H
#define NODE_H

#include "Includes.h"

class Node {
private:
    int id;
    double x,y;
public:

    Node(double x, double y);
    Node(int id, double x, double y);

    //Getters
    int getID() const;
    double getX() const;
    double getY() const;
    friend std::ostream& operator<<(std::ostream& os, const Node& n);
};
inline std::ostream& operator<<(std::ostream& os, const Node& n) {
    os << "[" << n.id << "]: (" << n.x << ", " << n.y << ")\n";
    return os;
}

#endif //NODE_H
