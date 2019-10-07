/* 
Author: Rachel Ng 
Course: CSCI-136
Instructor: Zamansky
Assignment: E5.14

Compares 2 numbers and switches them if the first is greater than the second
*/

#include <iostream>

void sort2(int& a, int& b) {
    if (a > b) {
        int c = a;
        a = b;
        b = c;
    }
}


int main() {
    int u = 2;
    int v = 3;
    int w = 4;
    int x = 1;
    
    std::cout << u << "\t" << v << std::endl;
    std::cout << w << "\t" << x << std::endl;
    
    sort2(u, v); // u is still 2, v is still 3
    sort2(w, x); // w is now 1, x is now 4

    std::cout << u << "\t" << v << std::endl;
    std::cout << w << "\t" << x << std::endl;


    return 0;
}
