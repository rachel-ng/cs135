/*
Author: Rachel Ng
Course: CSCI-136
Instructor: Zamansky
Assignment: Lab 1A

Finds the smallest number of 2
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
    cin >> a;
    cout << "Enter the second number: ";
    cin >> b;
    cout << "\n";
    cout << "The smaller of the two is " << smaller(a,b);
    cout << "\n";
}

