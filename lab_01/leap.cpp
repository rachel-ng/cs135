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

bool leap (int year) {
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
