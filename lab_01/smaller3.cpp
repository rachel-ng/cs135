/*
Author: your name
Course: CSCI-136
Instructor: their name
Assignment: title, e.g., Lab1A

Here, briefly, at least in one or a few sentences
describe what the program does.
*/


#include <iostream>
using namespace std;

int smaller (int a, int b) 
{
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

