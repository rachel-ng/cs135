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

class Triangle {
public:
    Point a;
    Point b;
    Point c;
};

double perimeter(Triangle d) {
    return distance(d.a, d.b) + distance(d.b,d.c), distance(d.c,d.a);
}


int main(){
    Point a, b, c;
    a.x = 1.1;
    a.y = 1.3;
    b.x = .9;
    b.y = 1.4;
    c.x = 2.1;
    c.y = 3.1;
    Triangle d = {a, b, c};
    std::cout << perimeter(d);
    return 0;
}
