/* 
Author: Rachel Ng 
Course: CSCI-136
Instructor: Zamansky
Assignment: Project 1A

Reads integers from std::cin and reports the sum 
*/

#include <iostream>


int main() {
    int s;
    int n = 0;
    while (std::cin >> s) {;
        n += s; // sums the numbers 
    }
    std::cout << n << std:;endl;
    return 0;
}
