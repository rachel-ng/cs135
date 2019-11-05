/*
Author: Rachel Ng
Course: CSCI-135
Instructor: Zamansky
Assignment: Lab 9

Coord3D, length, fartherFromOrigin, move
*/

#include <iostream>

std::string * createAPoemDynamically() {
    std::string *p = new std::string;
    *p = "Roses are red, violets are blue";
    return p;
}

int main() {
    while(true) {
        std::string *p;
        p = createAPoemDynamically();
        
        // assume that the poem p is not needed at this point

        delete p; 
    }
}

