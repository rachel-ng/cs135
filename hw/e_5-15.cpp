/* 
Author: Rachel Ng 
Course: CSCI-136
Instructor: Zamansky
Assignment: E5.15

Compares 3 numbers and arranges them in sorted order 
*/

#include <iostream>

void sort2(int& a, int& b) {
    if (a > b) {
        int c = a;
        a = b;
        b = c;
    }
}

void sort3(int& a, int& b, int& c) {
    sort2(b, c);
    sort2(a, b);
    sort2(b, c);
}


int main() {
    int v = 3;
    int w = 4;
    int x = 1;
    
    std::cout << v << "\t" << w << "\t" << x << std::endl;
    
    sort3(v, w, x); 

    std::cout << v << "\t" << w << "\t" << x << std::endl;

    return 0;
}
