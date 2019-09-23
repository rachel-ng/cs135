/* 
Author: Rachel Ng 
Course: CSCI-136
Instructor: Zamansky
Assignment: Lab 4G 

Takes a width and height
Prints a checkerboard made of 3x3 squares made of '*' with the specified dimensions
*/


#include <iostream>

int main() {

    int width, height;

    std::cout << "Input width: ";
    std::cin >> width;
    std::cout << "Input height: ";
    std::cin >> height;

    std::cout << "Shape: " << std::endl;

    int ww, hh;
    for (int h = 0; h < height; h++){ // rows
        for (int w = 0; w < width; w++){ // cols
            // 3x3 box
            ww = w;
            hh = h;
            if (ww % 3 == 1) {
                ww -= 1;
            }
            if (ww % 3 == 2) {
                ww -= 2;
            }
            if (hh % 3 == 1) {
                hh -= 1;
            }
            if (hh % 3 == 2) {
                hh -= 2;
            }
            
            // alternating pattern
            if (hh % 2 == ww % 2){
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
