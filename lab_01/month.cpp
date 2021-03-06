/*
Author: Rachel Ng
Course: CSCI-136
Instructor: Zamansky
Assignment: Lab 1D

Number of days in the given month
Dependent if it's a leap year or a common year 
*/


#include <iostream>

bool leap (int year) {
    // boolean with whether or not it's a leap year
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
    // int with the number of days in the given month 
    if (month == 2) {
        // feburary 
        if (leap(year)) {
            return 29;
        }
        else {
            return 28;
        }
    }
    // the other months
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
    std::cout << "Enter year: ";
    int y;
    std::cin >> y;

    std::cout << "Enter month: ";
    int m;
    std::cin >> m;

    std::cout << "\n";
    std::cout << days(m,y) << " days \n";    
}
