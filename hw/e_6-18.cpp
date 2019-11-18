/*
Author: Rachel Ng
Course: CSCI-135
Instructor: Maryash
Assignment: E6.18

Vector
*/


#include <iostream> 
#include <vector> 

std::vector<int> append(std::vector<int> a, std::vector<int> b) {
    std::vector<int> c;
    for (int i = 0; i < a.size(); i++) {
        c.push_back(a[i]);
    }

    for (int i = 0; i < b.size(); i++) {
        c.push_back(b[i]);
    }
    return c;
}

void printv (std::vector<int> a) {
    std::cout << "{";

    for (int i = 0; i < a.size() - 1; i++) {
        std::cout << a[i]; 
        std::cout << ", ";
    }

    std::cout <<  a[a.size()-1];
    std::cout << "}" << std::endl;
}

int main() {

    std::vector<int> d = {1, 4, 9, 16};
    std::vector<int> e = {9, 7, 4, 9, 11};
    std::vector<int> f = append(d,e);
   
    printv(f);

    return 0;
}
