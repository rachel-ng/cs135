/* 
Author: Rachel Ng 
Course: CSCI-136
Instructor: Zamansky
Assignment: E3.1

Takes an integer
Prints whether the integer is negative, zero, or positive
*/

#include <iostream> 
#include <string>

int main() {

    int intg;
    std::cin >> intg;
    
    if (intg < 0) {
        std::cout << "Negative" << std::endl;
    }
    else if (intg == 0) {
        std::cout << "Zero" << std::endl;
    }
    else { 
        std::cout << "Positive" << std::endl;
    }

    return 0;
}
