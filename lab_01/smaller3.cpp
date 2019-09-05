/*
Author: Rachel Ng
Course: CSCI-136
Instructor: Zamansky
Assignment: Lab 1B

Finds the smallest number of 3
*/

#include <iostream>

int smaller (int a, int b) {
    // finds the smaller of 2 nums
    if (a > b) {
        return b;
    }
    else {
        return a;
    }    
}

int main() {
    std::cout << "Enter the first number: ";
    int a; 
    int b;
    int c;
    std::cin >> a;
    std::cout << "Enter the second number: ";
    std::cin >> b;
    std::cout << "Enter the third number: ";
    std::cin >> c;
    std::cout << "\n";
    std::cout << "The smaller of the three is " << smaller(smaller(a,b),c); 
    std::cout << "\n";
}

