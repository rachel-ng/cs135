/* 
Author: Rachel Ng 
Course: CSCI-136
Instructor: Zamansky
Assignment: Lab 6

Caesar Cipher
shiftChar and encryptCaesar
*/

#include <iostream>

char shiftChar(char c, int rshift) {
    // shifts characters over by a specified number
    if (isalpha(c)) {
        int unshifted = c;
        int mod = (int)c >= 97 ? 97:65;
        return (char)(((unshifted + rshift) % mod) % 26) + mod;
    }
    else {
        return c;
    }
}

std::string encryptCaesar(std::string plaintext, int rshift) {
    std::string encrypted;
    for (int i = 0; i < plaintext.length(); i++) {
        int num = plaintext[i];
        if (isalpha(plaintext[i])) {
            encrypted += shiftChar(plaintext[i], rshift);
        }
        else {
            // doesn't encrypt if it's a space or nonalpha character
            encrypted += (char)num;
        }
    }
    return encrypted;
}

int main() {
    std::string plaintext; 
    int shift;
    getline(std::cin, plaintext);
    std::cin >> shift;
    std::cout << encryptCaesar(plaintext, shift);
    return 0;
}
