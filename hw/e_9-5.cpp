/*
Author: Rachel Ng
Course: CSCI-135
Instructor: Maryash
Assignment: E9.5

Rectangle
*/


#include <iostream> 

class Rectangle {
public: 
    Rectangle(double input_w, double input_h) {
        height = input_h; 
        width = input_w;
    }
    double get_perimeter() {
        return (2 * height) + (2 * width);
    }
    
    double get_area() {
        return height * width;
    }

    void resize(double factor) {
        height *= factor;
        width *= factor;
    }

private:
    double height;
    double width;
};
