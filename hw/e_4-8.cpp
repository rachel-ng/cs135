/* 
Author: Rachel Ng 
Course: CSCI-136
Instructor: Zamansky
Assignment: E4.8

Takes an input
Prints each of the characters of the given input
*/

#include <iostream> 
#include <string>

int main() {

    std::string word;

    std::cin >> word;
    std::cout << "\n";

    for (int i = 0; i < word.size(); i++) { 
        std::cout << word[i] << "\n";
    }

    return 0;
}
