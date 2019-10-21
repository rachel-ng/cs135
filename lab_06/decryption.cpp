/* 
Author: Rachel Ng 
Course: CSCI-136
Instructor: Zamansky
Assignment: Lab 6

Decrypt Caesar and Vigenere ciphers
    includes a function for unshifting chars, accounting for wrapping
*/

#include <iostream>

char shiftChar(char c, int rshift) {
    // shifts characters over by a specified number
    if (isalpha(c)) {
        int unshifted = c;
        // determines mod
        int mod = (int)c >= 97 ? 97:65;
        // shifts the char
        return (char)(((unshifted + rshift) % mod) % 26) + mod;
    }
    else {
        // doesn't do anything if nonalpha
        return c;
    }
}

char unshiftChar(char c, int rshift) {
    if (isalpha(c)) {
        int shifted = c;
        // determines mod
        int mod = (int)c >= 97 ? 97:65;
        // finds actual char
        shifted -= mod;
        // fixes character wrapping
        if (shifted < rshift) {
            shifted += 26;
        }
        // unshifts the char
        return (char)(shifted - rshift + mod);
    }
    else {
        // doesn't do anything if nonalpha
        return c;
    }
}

std::string encryptCaesar(std::string plaintext, int rshift) {
    std::string encrypted; 
    for (int i = 0; i < plaintext.length(); i++) {
        if (isalpha(plaintext[i])) {
            // if it's a letter
            encrypted += shiftChar(plaintext[i], rshift);
        }
        else {
            // if it's not a letter
            encrypted += plaintext[i];
        }
    }
    return encrypted;
}

std::string encryptVigenere(std::string plaintext, std::string keyword) {
    int count = 0;

    std::string encrypted; 
    for (int i = 0; i < plaintext.length(); i++) {
        int num = plaintext[i]; 
        if (isalpha(plaintext[i])) {
            // if it's a letter
            encrypted += shiftChar(num, ((int)keyword[(count % keyword.length())]-97));
            count++;
        }
        else {
            // if it's not a letter
            encrypted += (char)num;
        }
    }
    return encrypted;
}

std::string decryptCaesar(std::string ciphertext, int rshift){ 
    std::string decrypted; 
    for (int i = 0; i < ciphertext.length(); i++) {
        if (isalpha(ciphertext[i])) {
            // if it's a letter
            decrypted += unshiftChar(ciphertext[i], rshift);
        }
        else {
            // if it's not a letter
            decrypted += (char)ciphertext[i];
        }
    }
    return decrypted;

}

std::string decryptVigenere(std::string ciphertext, std::string keyword) {
    int count = 0;

    std::string decrypted; 
    for (int i = 0; i < ciphertext.length(); i++) {
        int num = ciphertext[i]; 
        if (isalpha(ciphertext[i])) {
            // if it's a letter
            decrypted += unshiftChar(ciphertext[i], ((int)keyword[(count % keyword.length())]-97));
            count++;
        }
        else {
            // if it's not a letter
            decrypted += (char)ciphertext[i];
        }
    }
    return decrypted;
}


int main() {
    std::string plaintext; 
    int cshift;
    std::string vshift;
    std::cout << "Enter plaintext: ";
    getline(std::cin, plaintext);
    
    std::cout << "= Caesar =\nEnter shift\t\t: ";
    std::cin >> cshift;
    std::cout << "Ciphertext\t\t: " << encryptCaesar(plaintext, cshift) << std::endl;
    std::cout << "Decrypted\t\t: " << plaintext << std::endl; 
    
    std::cout << "= Vigenere =\nEnter shift\t\t: ";
    std::cin >> vshift;
    std::cout << "Ciphertext\t\t: " << encryptVigenere(plaintext, vshift) << std::endl;
    std::cout << "Decrypted\t\t: " << plaintext << std::endl;
    
    return 0;
}
