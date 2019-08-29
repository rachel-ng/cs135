#include <iostream>

int fib (int n) {
    if (n == 0) {
        return 0;
    }
    else if (n == 1) {
        return 1;
    }
    else {
        return fib(n - 1) + fib(n - 2);
    }

}

int main() {
    
    std::cout << "gimme a number: ";
    
    int a;
    std::cin >> a; 

    std::cout << "here's the fib of a: " << fib(a) << "\n";

    return 0;

}

