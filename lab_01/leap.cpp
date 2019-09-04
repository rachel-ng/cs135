/*
Author: Rachel Ng
Course: CSCI-136
Instructor: Zamansky
Assignment: Lab 1C

When given a year
Tells you if it's a leap year or a common year 
*/


#include <iostream>
using namespace std;

bool leap (int year) {
    // returns a boolean with whether or not it's a leap year 
    if (year % 4 != 0) {
        return false;
    }
    else if (year % 100 != 0) {
        return true;
    }
    else if (year % 400 != 0) {
        return false;
    }
    else {
        return true;
    }
 
}
int main() {
    cout << "Enter year: ";
    int y;
    cin >> y;
    cout << "\n";
    if (leap(y) == true) {
        cout << "Leap year\n";
    }
    else {
        cout << "Common year\n";
    }
}
