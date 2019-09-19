/* 
Author: Rachel Ng 
Course: CSCI-136
Instructor: Zamansky
Assignment: Project 1C

A calculator that takes multiple formulas
*/


#include <iostream>
#include <string>


int main() {
    int s;
    int n = 0;
    char op = '+';
    while (std::cin >> s) {
        if (op == '+') {
            n += s;
        }
        else if (op == '-') {
            n -= s;
        }
        else if (op == ';') {
            // if there's a semicolon the function terminates
            std::cout << n << std::endl;
            n = s;
        }
        std::cin >> op;
    }
    std::cout << n << std::endl;
    return 0;
}
