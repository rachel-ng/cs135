/* 
Author: Rachel Ng
Course: CSCI-135
Instructor: Maryash
Assignment: E5.21

Recursive reverse string
*/

#include <iostream> 
#include <string> 

std::string reverse(std::string str) {
    if (str.size() == 1) {
        return str;
    } 
    else {
        return reverse(str.substr(1)) + str.substr(0,1);
    }
}

int main () {

    std::cout << reverse("low") << std::endl;
    std::cout << reverse("wolf") << std::endl;
    std::cout << reverse("racecar") << std::endl;
    
    return 0;
}
