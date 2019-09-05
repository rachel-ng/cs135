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

    std::cout  << "Numbers of gallons of gas in the tank? "; 
    std::cin >> gals; 

    std::cout  << "Fuel efficiency in miles per gallon? "; 
    std::cin >> eff;

    std::cout  << "Price of gas per gallon? "; 
    std::cin >> price;

    std::cout << "\n";

    std::cout << costmill(eff, price); 

    std::cout << "\n";
    
    std::cout << dist(gals, eff); 

    std::cout << "\n";
    
    return 0; 
}
