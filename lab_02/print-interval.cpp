/* 
Author: Rachel Ng 
Course: CSCI-135
Assignment: Lab 2B

Prints all numbers in a given range
Includes the lower limit, but not the upper limit
*/

#include <iostream>
#include <string>

int main() {
    int l, u;
    std::cout << "Please enter L: " ;
    std::cin >> l;
    std::cout << "Please enter U: " ;
    std::cin >> u;
    std::string s;
    for(int i = l; i < u; i++) {
        // converts int to string and then adds the space
        s += std::to_string(i) + " ";
    }
    std::cout << s << std::endl;
}
