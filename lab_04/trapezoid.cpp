/* 
Author: Rachel Ng 
Course: CSCI-136
Instructor: Zamansky
Assignment: Lab 4F

Takes a width and height
Prints a trapezoid with the specified width and height
*/


#include <iostream>

int main() {

    int width, height;

    std::cout << "Input width: ";
    std::cin >> width;
    std::cout << "Input height: ";
    std::cin >> height;

    if ((height > width / 2 and width % 2 == 0) or (height > (width + 1) / 2 and width % 2 == 1)) {
        std::cout << "Impossible shape!" << std::endl;
    }
    else {
        std::cout << "Shape: " << std::endl;

        for (int h = 0; h < height; h++){ 
            for (int w = 0; w < width; w++){
                if (w >= h and w <= width - 1 - h) {
                    // trapezoid 
                    std::cout << "*";
                }
                else {
                    std::cout << " ";
                }
            }
            std::cout << "\n";
        }
    }

    return 0;

}
