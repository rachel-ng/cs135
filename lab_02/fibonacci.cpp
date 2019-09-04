/* 
Author: Rachel Ng 
Course: CSCI-136
Instructor: Zamansky
Assignment: Lab 2D

Computes fibonacci numbers 1 - 60
Uses an array to store ints
*/

#include <iostream>

int main() {
    // make an array
    int fib[60];
    // first two terms are given
    fib[0] = 0;
    fib[1] = 1;
    // and all the following ones can be computed iteratively as
    for (int i = 2; i < 60; i++) {
        fib[i] = fib[i-1] + fib[i-2];
        std::cout << fib[i] << "\n";
    }
    for (int i = 0; i < 60; i++) {
        std::cout << i << "\t" << fib[i] << "\n";
    }


}
