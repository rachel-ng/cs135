/* 
Author: Rachel Ng 
Course: CSCI-135
Assignment: Project 1A

Validates numbers read from std::in
Numbers must be 0 < s < 100
Asks you to re-enter if the number is invalid
Prints the square of the number
*/

#include <iostream>

int main() {
    std::cout << "Please enter an integer: " ;
    int s;
    while(std::cin >> s and (s < 1 or s > 99)) {
        // if the number is invalid, asks you to re-enter
        std::cout << "Please re-enter: " ;
    }
    // prints squared number
    std::cout << "Number squared is " << s * s << std::endl;
    return 0;
}
