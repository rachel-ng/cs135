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

int days (int month, int year) {
    if (month == 2) {
        if (leap(year)) {
            return 29;
        }
        else {
            return 28;
        }
    }
    else if (month < 8) {
        if (month % 2 != 0) {
            return 31;
        }
        else {
            return 30;
        }
    }
    else { 
        if (month % 2 != 0) {
            return 30;
        }
        else {
            return 31;
        }
    }
}

int main() {
    cout << "Enter year: ";
    int y;
    cin >> y;

    cout << "Enter month: ";
    int m;
    cin >> m;

    cout << "\n";
    cout << days(m,y) << "days \n";    
}
