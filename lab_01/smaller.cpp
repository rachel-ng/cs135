/*
Author: Rachel Ng
Course: CSCI-136
Instructor: Zamansky
Assignment: Lab 1A

Finds the smallest number of 2
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
    std::cin >> a;
    std::cout << "Enter the second number: ";
    std::cin >> b;
    std::cout << "\n";
    std::cout << "The smaller of the two is " << smaller(a,b);
    std::cout << "\n";
}

