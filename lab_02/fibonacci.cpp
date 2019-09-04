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
As the numbers approach 2 billions they begin to switch between negative and positive at random. 
The negative numbers stay the same when the program has been run multiple times separately. 
It seems like there's a limit on how big an integer can get in C++. 
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
