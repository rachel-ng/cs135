/* 
Author: Rachel Ng 
Course: CSCI-136
Instructor: Zamansky
Assignment: Lab 4C 

Takes a dimension
Prints a diagonal cross of that dimension
*/


#include <iostream>

int main() {
    int size;

    std::cout << "Input size: ";
    std::cin >> size;

    std::cout << "Shape: " << std::endl;

    for (int h = 0; h < size; h++){ // rows
        for (int w = 0; w < size; w++){ // cols
            // diagonal cross pattern
            if (w == h or w == size - 1 - h) { 
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
