/* 
Author: Rachel Ng 
Course: CSCI-136
Instructor: Zamansky
Assignment: Lab 7

remove leading spaces
*/

#include <iostream>

std::string removeLeadingSpaces(std::string line) {
    for (int i = 0; i < line.size(); i++) {
        if (!isspace(line[i])) {
            // if it's not a space, return the rest fo the line
            return line.substr(i,line.size() - i);
        }
        else {
            continue;
        }
    }
    return line;
}


int main() {
    std::string s;
    while(getline(std::cin, s)) {
        std::cout << removeLeadingSpaces(s) << std::endl;
    }

    return 0;
}
