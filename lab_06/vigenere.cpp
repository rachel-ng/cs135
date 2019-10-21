/* 
Author: Rachel Ng 
Course: CSCI-136
Instructor: Zamansky
Assignment: Lab 6

Vignere Cipher
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

std::string encryptVigenere(std::string plaintext, std::string keyword) {
    int count = 0;
    // count for which letter letter it should shift over
    std::string encrypted; 
    for (int i = 0; i < plaintext.length(); i++) {
        int num = plaintext[i]; 
        if (isalpha(plaintext[i])) {
            encrypted += shiftChar(num, ((int)keyword[(count % keyword.length())]-97));
            count++;
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
    std::string shift;
    getline(std::cin, plaintext);
    std::cin >> shift;
    std::cout << encryptVigenere(plaintext, shift);
    return 0;
}
