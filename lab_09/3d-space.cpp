/*
Author: Rachel Ng
Course: CSCI-135
Instructor: Zamansky
Assignment: Lab 9

Coord3D, length, fartherFromOrigin, move
*/

#include <iostream> 
#include <cmath>

class Coord3D {
public:
    double x;
    double y;
    double z;
};


double length(Coord3D *p) {
    return sqrt(pow((*p).x, 2) + pow((*p).y, 2) + pow((*p).z, 2));
}

Coord3D * fartherFromOrigin(Coord3D *p1, Coord3D *p2) {
    double l1 = length(p1);
    double l2 = length(p2);
    return l1 > l2 ? p1 : p2;
}

void move(Coord3D *ppos, Coord3D *pvel, double dt) {
    (*ppos).x = (*ppos).x + (*pvel).x * dt;
    (*ppos).y = (*ppos).y + (*pvel).y * dt;
    (*ppos).z = (*ppos).z + (*pvel).z * dt;
}

int main() {
    
    Coord3D pointP = {10, 20, 30};
    
    // test length
    std::cout << length(&pointP) << std::endl; // would print 37.4166
    
    Coord3D pointQ = {-20, 21, -22};

    std::cout << "Address of P: " << &pointP << std::endl;
    std::cout << "Address of Q: " << &pointQ << std::endl << std::endl;
    
    // test fartherFromOrigin
    Coord3D * ans = fartherFromOrigin(&pointP, &pointQ);
   
    std::cout << "ans = " << ans << std::endl; // So which point is farther?
   
    Coord3D pos = {0, 0, 100.0};
    Coord3D vel = {1, -5, 0.2};
    
    // test move
    move(&pos, &vel, 2.0); // object pos gets changed
    std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;
    // prints: 2 -10 100.4

    return 0;
}
