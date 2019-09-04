/* 
Author: Rachel Ng 
Course: CSCI-136
Instructor: Zamansky
Assignment: E2.10

Given the gallons of gas in a tank, fuel efficiency in miles per gallon, and the price of gas per gallon 
Prints the cost per 100 miles and how far a car can go with the gas in the tank 
*/


#include <iostream>
#include <string>

using namespace std;

int main() {
    int s;
    int n = 0;
    char op = '+';
    while (cin >> s) {;
        if (op == '+') {
            n += s;
        }
        else if (op == '-') {
            n -= s;
        }
        else if (op == ';') {
            cout << n << endl;
            n = s;
        }
        cin >> op;
    }
    cout << n << endl;
    return 0;
}
