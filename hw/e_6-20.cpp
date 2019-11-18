/*
Author: Rachel Ng
Course: CSCI-135
Instructor: Maryash
Assignment: E6.20

Vector
*/


#include <iostream> 
#include <vector> 

std::vector<int> merge_sorted(std::vector<int> a, std::vector<int> b) {
    std::vector<int> c;
    int as = 0;
    int bs = 0;
    
    while(as < a.size() && bs < b.size()) {
        if (a[as] < b[bs]) {
            c.push_back(a[as]);
            as++;
        }
        else {
            c.push_back(b[bs]);
            bs++;
        }
    }

    while(as < a.size()) {
        c.push_back(a[as]);
        as++;
    }
    
    while(bs < b.size()) {
        c.push_back(b[bs]);
        bs++;
    }
    
    return c;
}

int main() {

    return 0;
}
