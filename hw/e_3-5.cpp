/* 
Author: Rachel Ng 
Course: CSCI-136
Instructor: Zamansky
Assignment: E3.5

Takes 3 integers
Prints whether the integers are increasing, decreasing, or neither
*/

#include <iostream> 
#include <string>

int main() {

    int intg1, intg2, intg3;
    std::cin >> intg1 >> intg2 >> intg3;
    
    if (intg1 == intg2 or intg1 == intg2 or intg2 == intg3) {
        std::cout << "Neither" << std::endl;
    }
    else if (intg1 < intg2 and intg2 < intg3) {
        std::cout << "Increasing" << std::endl;
    }
    else if (intg1 > intg2 and intg2 > intg3) {
        std::cout << "Decreasing" << std::endl;
    }
    else {
        std::cout << "Neither" << std::endl;
    }

    return 0;
}
