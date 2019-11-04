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
    std::cout << x << std::endl;
    double y = distance(d.b,d.c);
    std::cout << y << std::endl;
    double z = distance(d.c,d.a);
    std::cout << z << std::endl;
    return x + y + z;
}


int main(){
    double f,g,h,i,j,k;
    std::cin >> f >> g >> h >> i >> j >> k; 
    Point a = {f, g};
    Point b = {h, i};
    Point c = {j, k};
    Triangle d = {a, b, c};
    std::cout << distance (b, a) << std::endl;
    std::cout << distance (b, c) << std::endl;
    std::cout << distance (a, c) << std::endl;
/*    std::cout << d.a.x << std::endl;
    std::cout << d.a.y << std::endl;
    std::cout << d.b.x << std::endl;
    std::cout << d.b.y << std::endl;
    std::cout << d.c.x << std::endl;
    std::cout << d.c.y << std::endl;
*/    std::cout << perimeter(d);
    return 0;
}
