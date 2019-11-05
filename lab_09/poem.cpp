/*
Author: Rachel Ng
Course: CSCI-135
Instructor: Zamansky
Assignment: Lab 9

Poem assignment 
*/

#include <iostream>

using namespace std;

string * createAPoemDynamically() {
    string *p = new string;
    *p = "Roses are red, violets are blue";
    return p;
}

int main() {
    while(true) {
        string *p;
        p = createAPoemDynamically();

        // assume that the poem p is not needed at this point
        
        delete p;
    }
}

