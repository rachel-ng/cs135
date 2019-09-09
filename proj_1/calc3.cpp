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

        if (ope == '^') {
            if (op == '+') {
                n += s * s;
            }
            else if (op == '-') {
                n -= s * s;
            }
            std::cin >> op; 
            if (op == ';') {
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
        else if (ope == ';') {
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
