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
    private: 
        double x;
        double y;
    public: 
        Point();
        Point(double, double);
    public:
        double getX() {
            return x;
        }
        double getY() {
            return y;
        }
};


double distance(Point a, Point b) {
    return pow(pow((b.getX() - a.getX()), 2) - pow((b.getY() - a.getY()),2), 0.5);
}

int main(){
    Point a, b;
    a = Point(1,2);
    b = Point(2,3);
    std::cout << distance(a,b);
    return 0;
}
