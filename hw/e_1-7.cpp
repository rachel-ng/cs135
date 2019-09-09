/* 
Author: Rachel Ng 
Course: CSCI-136
Instructor: Zamansky
Assignment: E1.7

Takes and prints 3 lines
*/

#include <iostream>
#include <string>

int main() {
    std::cout << "Enter 3 items!\n";
    std::string uno, dos, tres;
    std::cout << "Numero uno: ";
    std::cin >> uno;
    std::cout << "Numero dos: ";
    std::cin >> dos;
    std::cout << "Numero tres: ";
    std::cin >> tres;
    std::cout << "\n";
    std::cout << uno;
    std::cout << "\n";
    std::cout << dos;
    std::cout << "\n";
    std::cout << tres;
    std::cout << "\n";
    
    return 0;
}
