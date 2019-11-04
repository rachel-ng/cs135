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


double distance (Point a, Point b) {
    double x = b.x - a.x;
    double y = b.y - a.y;
    double z = pow(x,2) + pow(y,2);
    return pow(z, 0.5);
}

int main(){
    Point a, b;
    std::cout << "Point a" << std::endl;
    std::cout << "x: " ;
    std::cin >> a.x;
    std::cout << "y: " ;
    std::cin >> a.y;
    std::cout << "Point b" << std::endl;
    std::cout << "x: " ;
    std::cin >> b.x;
    std::cout << "y: " ;
    std::cin >> b.y;
    
    std::cout << distance(a,b) << std::endl;
    return 0;
}
