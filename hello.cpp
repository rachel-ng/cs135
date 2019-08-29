#include <iostream> 

int add2 (int a, int b) {
    return a + b;
}



int main() {
    
    int a;

    std::cout << "hello world!" << std::endl;
    std::cout << 22 << " " << 123.45 << "\n";

    std::cout << "Enter a number: ";
    std::cin >> a;

    std::cout << "You entered " << a << "\n";

    // wow an if else 

    if (a > 10) {
        std::cout << "a is not v smol\n";
    }
    else {
        std::cout << "a is smol\n";
    }

    // a while loop?? amazing. 

    a = 0;
    while (a < 10) {
        std:: cout << a << " ";
        a = a + 1;
    }

    std::cout << "\n";

    // a for loop!!

    for (int i; i < 10; ++i) {
        std::cout << "i=" << i << " ";
    }

    std::cout << "\n";
    
    // a function

    int c = add2(a,12);
    
    std::cout << c << " ";

    std::cout << "\n";
    
    return 0;
}

