/* 
Author: Rachel Ng 
Course: CSCI-136
Instructor: Zamansky
Assignment: E1.7

Takes and prints 3 lines
*/

#include <iostream>

std::string middle (std::string str) {
    int mid = str.length();
    return str.substr((mid - 1)/2, mid % 2 == 0 ? 2 : 1);
}


int main() {
    std::string word;
    std::cin >> word;

    std::cout << middle(word) << std::endl;

    return 0;
}
