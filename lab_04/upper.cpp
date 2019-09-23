/* 
Author: Rachel Ng 
Course: CSCI-136
Instructor: Zamansky
Assignment: Lab 4E

Takes a length
Prints a triangle / upper right half of a square with that length
*/


#include <iostream>

int main() {
    int length;

    std::cout << "Input side length: ";
    std::cin >> length;

    std::cout << "Shape: " << std::endl;

    for (int h = 0; h < length; h++){ // rows
        for (int w = 0; w < length; w++){ // cols
            // the parts of the triangle
            if (w >= h) { 
                std::cout << "*"; 
            }
            else {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }

    return 0;

}
