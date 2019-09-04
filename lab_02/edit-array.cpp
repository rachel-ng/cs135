/* 
Author: Rachel Ng 
Course: CSCI-135
Assignment: Lab 2C

Creates an array of 10 integers
Allows user to edit any of its elements
*/

#include <iostream>

int main() {
    int myData[10];
    for (int i = 0; i < 10; i++) {
        myData[i] = 1;
    }
    int i = 0;
    int v;
    do {
        std::cout << "\n"; 
        
        std::string s;
        for (int i = 0; i < 10; i++) {
            s += std::to_string(myData[i]) + " "; 
        }
        
        std::cout << s << std::endl; // print the array
        std::cout << "\n"; 
        
        // get i and v from the user
        std::cout << "Input index: ";
        std::cin >> i;
        std::cout << "Input value: ";
        std::cin >> v;
        
        // if i is good, update the array at index i
        if (i > -1 and i < 10) {
            myData[i] = v;
        }
    } 
    while (i > -1 and i < 10); // if the index was good, repeat
 
    std::cout << "Index out of range. Exit.\n"; 
}
