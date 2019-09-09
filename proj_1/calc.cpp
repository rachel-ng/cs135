/* 
Author: Rachel Ng 
Course: CSCI-136
Instructor: Zamansky
Assignment: Project 1B

Caclulator that can add and subtract integers
Takes typed input or from a file
*/


#include <iostream>
#include <string>


int main() {
    int s;
    int n = 0;
    char op = '+';
    while (std::cin >> s) {;
        if (op == '+') {
            n += s;
        }
        else if (op == '-') {
            n -= s;
        }
        std::cin >> op;
    }
    std::cout << n << std::endl;
    return 0;
}
