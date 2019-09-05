/* 
Author: Rachel Ng 
Course: CSCI-136
Instructor: Zamansky
Assignment: Lab 2D

Computes fibonacci numbers 1 - 60
Uses an array to store ints
*/

#include <iostream>

/*
As the numbers approach 2 billion they begin to overflow because it is larger than the number can hold.
ints have a range limited to -2147483648 to 2147483647, and when it goes over that the numbers are truncated to fit. 
*/

int main() {
    // make an array
    int fib[60];
    // first two terms are given
    fib[0] = 0;
    fib[1] = 1;
    // and all the following ones can be computed iteratively as
    for (int i = 2; i < 60; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }
    for (int i = 0; i < 60; i++) {
        std::cout << fib[i] << std::endl;
    }
}
