/* 
Author: Rachel Ng 
Course: CSCI-135
Assignment: Project 1A

Reads integers from std::cin and reports the sum 
*/

#include <iostream>

using namespace std;

int main() {
    int s;
    int n = 0;
    while (cin >> s) {;
        n += s; // sums the numbers 
    }
    cout << n << endl;
    return 0;
}
