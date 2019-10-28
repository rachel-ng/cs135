/*
Author: Rachel Ng
Course: CSCI-135
Instructor: Maryash
Assignment: E6.8

Returns whether arrays are equal
*/

#include <iostream>

bool equals(int a[], int a_size, int b[], int b_size) {
    if (a_size != b_size) {
        return false;
    }
    else {
        for(int i = 0; i < a_size; i++) {
            if (a[i] != b[i]) {
                return false;
            }
        }
        return true;
    }
}

int main() {
    int a[3] = [1,2,3];
    int b[3] = [1,3,2];

    std::cout << equals(a,3,b,3);

    return 0;
}

