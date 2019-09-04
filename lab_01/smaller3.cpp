/*
Author: Rachel Ng
Course: CSCI-136
Instructor: Zamansky
Assignment: Lab 1B

Finds the smallest number of 3
*/

#include <iostream>
using namespace std;

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
    cout << "Enter the first number: ";
    int a; 
    int b;
    int c;
    cin >> a;
    cout << "Enter the second number: ";
    cin >> b;
    cout << "Enter the third number: ";
    cin >> c;
    cout << "\n";
    cout << "The smaller of the three is " << smaller(smaller(a,b),c); 
    cout << "\n";
}

