/*
Author: Rachel Ng
Course: CSCI-135
Instructor: Maryash
Assignment: E7.16

Distance between points
*/

#include <iostream> 
#include <cmath>

class Point {
public:
    double x;
    double y;
};


double distance(Point a, Point b) {
    return pow((pow((b.x - a.x), 2) - pow((b.y - a.y),2)), 0.5);
}

int main(){
    Point a, b;
    a.x = 1.1;
    a.y = 1.3;
    b.x = .9;
    b.y = 1.4;
    std::cout << distance(a,b);
    return 0;
}
