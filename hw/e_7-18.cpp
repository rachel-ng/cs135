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
    double x = distance(d.a, d.b);
    double y = distance(d.b,d.c);
    double z = distance(d.c,d.a);
    return x + y + z;
}


int main(){
    Point a, b, c;
    a.x = 1;
    a.y = 3;
    b.x = 5;
    b.y = 7;
    c.x = 2;
    c.y = 5;
    Triangle d = {a, b, c};
    std::cout << d.a << std::endl;
    std::cout << d.b << std::endl;
    std::cout << d.c << std::endl;
    std::cout << perimeter(d);
    return 0;
}
