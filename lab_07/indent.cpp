/* 
Author: Rachel Ng 
Course: CSCI-136
Instructor: Zamansky
Assignment: Lab 7

Indentation
*/

#include <iostream>
#include <cctype>

std::string removeLeadingSpaces(std::string line) {
    for (int i = 0; i < line.size(); i++) {
        if (!isspace(line[i])) {
            return line.substr(i,line.size() - i);
        }
        else {
            continue;
        }
    }
    return line;
}

int countChar(std::string line, char c) {
    int n = 0;
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == c) {
            n++;
        }
    }
    return n;
}

std::string tabs (int n) {
    std::string t = "";
    for (int i = 0; i < n; i++) {
        t += "\t";
    }
    return t;
}

int main() {
    std::string s;
    int indent = 0;

    while(getline(std::cin, s)) {
        std::string r = removeLeadingSpaces(s);
        int c = r[0] == '}' ? 1 : 0;
        std::cout << tabs(indent - c) << r << std::endl;
        indent += countChar(r,'{') - countChar(r,'}'); 
    }

    return 0;
}
