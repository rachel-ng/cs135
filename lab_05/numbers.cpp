/* 
Author: Rachel Ng 
Course: CSCI-136
Instructor: Zamansky
Assignment: Lab 5

A file with all the functions from lab 5
    bool isDivisbleBy(int n, int d);
    bool isPrime(int n);
    int nextPrime(int n);
    int countPrimes(int a, int b);
    bool isTwinPrime(int n);
    int nextTwinPrime(int n);
    int nextTwinPrime(int n);
*/

#include <iostream>

bool isDivisibleBy(int n, int d) {
    // checks if a number (n) is divisble by another number (d)
    if (d == 0) {
        return false;
    }
    if (n % d == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool isPrime(int n) {
    int d = 0; 
    int f = 0;
    for (int d = 1; d < n; d++) {
        if (isDivisibleBy(n,d)) {
             f++;
        }
    }
    if (f != 1) {
         return false;
    }
    else {
         return true;
    }
}

int nextPrime(int n) {
    // finds the next prime greater than n
    int p = n + 1;
    while (!isPrime(p)) {
        p++;
    }
    return p;
}

int prevPrime(int n) {
    // finds the previous prime less than n
    int p = n + 1;
    while (!isPrime(p) and p > -1) {
        p--;
    }
    return p;
}

int countPrimes(int a, int b) {
    // counts all the primes in a range
    int c = a;
    int t = 0;
    while (c < b + 1) {
        if(isPrime(c)) {
            t++;
        }
        c++;
    }
    return t;
}

bool isTwinPrime(int n) {
    // checks if a number is a twin prime
    // if n-2 or n+2 (or both) are prime numbers, then n is a twin prime
    if (isPrime(n) and (isPrime(n - 2) or isPrime(n + 2))) {
        return true;
    }
    return false;
}

int nextTwinPrime(int n) {
    // finds the next twin prime greater than n
    int p = n + 1;
    while (!isTwinPrime(p)) {
        p++;
    }
    return p;
}

int largestTwinPrime(int a, int b) {
    // finds the largest twin prime within a range 
    int c = b;
    int m = -1;
    while (c > a - 1){
        if (isTwinPrime(c)) {
            return c;
        }
        else {
            c--; 
        }
    }
    return m;
}

int main() {
    int n, d;
    
    std::cin >> n >> d;

    if (isDivisibleBy(n,d)) {
        std::cout << "Yes" << std::endl;
    }
    else {
        std::cout << "No" << std::endl;
    }
    std::cin >> n;
    if (isPrime(n)) {
        std::cout << "Yes" << std::endl;
    }
    else {
        std::cout << "No" << std::endl;
    }
    std::cin >> n;
    std::cout << nextPrime(n) << std::endl;

    std::cin >> n >> d;
    std::cout << largestTwinPrime(n,d) << std::endl;
    
    return 0;
}
