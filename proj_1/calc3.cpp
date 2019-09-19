/* 
Author: Rachel Ng 
Course: CSCI-136
Instructor: Zamansky
Assignment: Project 1D

A calculator that takes multiple formulas
Also accounts for squares
*/


#include <iostream>
#include <string>

int main() {
    int s;
    int n = 0;
    char ope;
    char op = '+';
    while (std::cin >> s) {
        std::cin >> ope;

        if (ope == '^') { // handles square
            if (op == '+') {
                n += s * s;
            }
            else if (op == '-') {
                n -= s * s;
            }
            std::cin >> op; 
            if (op == ';') { // checks if it terminates at the next char
                if (op == '+') {
                    n += s;
                }
                else if (op == '-') {
                    n -= s;
                }

                std::cout << n << std::endl;
                
                op = '+';
                n = 0;
            }
        }
        else if (ope == ';') { // if formula terminates
            if (op == '+') {
                n += s;
            }
            else if (op == '-') {
                n -= s;
            }

            std::cout << n << std::endl;
            op = '+';
            n = 0;
        }
        else {
            if (op == '+') {
                n += s;
                op = ope;   
            }
            else if (op == '-') {
                n -= s;
                op = ope;   
            }
        }
    }
    
    return 0;
}
