/*
Author: Rachel Ng
Course: CSCI-135
Instructor: Maryash
Assignment: E7.1

Returns whether arrays are equal
*/

#include <iostream>

void sort2(double* p, double* q) {
    if (*q < *p) {
        double o = *p;
        *p = *q;
        *q = o;
    }
}


int main() {
    double x = 1.1;
    double y = 0.3;
    std::cout << x << "\t" << y << std::endl;
    sort2(&x, &y);
    std::cout << x << "\t" << y << std::endl;
    return 0;
}
