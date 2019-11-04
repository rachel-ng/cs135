/*
Author: Rachel Ng
Course: CSCI-135
Instructor: Maryash
Assignment: E7.18

Distance between points
Perimeter of triangle
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
    // std::cout << x << std::endl;
    // std::cout << y << std::endl;
    // std::cout << z << std::endl;
    return x + y + z;
}


int main(){
    double f,g,h,i,j,k;
    std::cin >> f >> g >> h >> i >> j >> k; 
    Point a = {f, g};
    Point b = {h, i};
    Point c = {j, k};
    Triangle d = {a, b, c};
/*    std::cout << d.a.x << std::endl;
    std::cout << d.a.y << std::endl;
    std::cout << d.b.x << std::endl;
    std::cout << d.b.y << std::endl;
    std::cout << d.c.x << std::endl;
    std::cout << d.c.y << std::endl;
*/    std::cout << perimeter(d);
    return 0;
}
