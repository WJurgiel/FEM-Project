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
    bool isBC;
    double temperature;
public:

    Node(double x, double y, bool isBC = false);
    //every node is created
    Node(int id, double x, double y, bool isBC = false);

    //Getters
    int getID() const;
    double getX() const;
    double getY() const;
    //This setter should be always called in constructor when reading BC
    void setBC(bool val);
    void setTemperature(double Tot);
    bool getBC() const;
    friend std::ostream& operator<<(std::ostream& os, const Node& n);
};
inline std::ostream& operator<<(std::ostream& os, const Node& n) {
    os << "[" << n.id << "]: (" << n.x << ", " << n.y << ") temp: " << n.temperature <<
        " isBC = " <<  n.isBC << "\n";
    return os;
}

#endif //NODE_H
