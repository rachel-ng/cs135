/* 
Author: Rachel Ng 
Course: CSCI-136
Instructor: Zamansky
Assignment: Lab 6

Testing ASCII conversion
*/

#include <iostream>

void ascii(std::string text) {
    for (int i = 0; i < text.length(); i++) {
        std::cout << text[i] << " " << (int)text[i] << std::endl;
    }
}

int main () {
    std::string words;
    getline(std::cin, words);
    ascii(words);
    return 0;
}

