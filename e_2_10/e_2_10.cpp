/* 
Author: Rachel Ng 
Course: CSCI-136
Instructor: Zamansky
Assignment: E2.10

Given the gallons of gas in a tank, fuel efficiency in miles per gallon, and the price of gas per gallon 
Prints the cost per 100 miles and how far a car can go with the gas in the tank 
*/


#include <iostream>
using namespace std;


double costmill (double eff, double price) {
    // cost per 100 miles 
    return (100 / eff) * price;
}

double dist (double gals, double eff) { 
    // how far the car can go with the gas in the tank 
    return gals * eff; 
} 

int main () {

    double gals, eff, price; 

    cout  << "Numbers of gallons of gas in the tank? "; 
    cin >> gals; 

    cout  << "Fuel efficiency in miles per gallon? "; 
    cin >> eff;

    cout  << "Price of gas per gallon? "; 
    cin >> price;

    cout << "\n";

    cout << costmill(eff, price); 

    cout << "\n";
    
    cout << dist(gals, eff); 

    cout << "\n";
    
    return 0; 
}
