/* 
Author: Rachel Ng 
Course: CSCI-135
Instructor: Maryash
Assignment: Project 2

Pronunciation dictionary
*/


#include <iostream>
#include <fstream>

void upper(char & a){
    int c = a;
    if (c > 96 && c < 123 && c != 39){
        // get the uppercase letter
        a = (char)c - 32;
    }
}

bool isalph(char c) {
    if ((c > 64 && c < 91) || (c > 96 && c < 123)) {
        // if it's a capital or lowercase letter
        return true;
    }
    if (c == 39) {
        // if it's an apostrophe '
        return true;
    }
    else {
        return false;
    }
}

void splitOnSpace(std::string s, std::string & before, std::string & after) {
    // reset strings
    before = ""; 
    after = "";
    // accumulate before space
    int i = 0;
    while (i < s.size() && not isspace(s[i])) { 
        before = before + s[i]; 
        i++; 
    }
    // skip the space
    i++;
    // accumulate after space
    while (i < s.size()) { 
        after = after + s[i]; 
        i++; 
    }
}

int countSpaces(std::string s) {
    int spaces = 0;
    for (int i = 0; i < s.length(); i++){
        if (isspace(s[i])) {
            // if it's a space add it to the count
            spaces += 1;
        }
    }
    return spaces;
}

bool identicalPronun (std::string word, std::string wordpron, std::string dup, std::string duppron) {
    if (wordpron == duppron && word != dup) {
        // if the pronunciation is the same, and they're different words
        return true;
    }
    else {
        return false;
    }
}

bool checkReplace (std::string word, std::string wordpron, std::string dup, std::string duppron) {
    int len = 0;
    int sim = 0;
    
    std::string wb, wa, db, da;
    wa = wordpron;
    da = duppron;
   
    for (int i = 0; i < countSpaces(duppron) + 1; i++){ 
        len ++;
        
        splitOnSpace(wa,wb,wa);
        splitOnSpace(da,db,da);
        if (wb == db) {
            // count the similarity
            sim ++;
        }
    }

    if (sim == len - 1) {
        // check if the similarity is only missing one
        // they're the same length, so it should be len - 1
        return true;
    }
    else {
        return false;
    }
}

bool checkAdd (std::string word, std::string wordpron, std::string dup, std::string duppron) {
    int len = 0;
    int sim = 0;
    
    std::string wb, wa, db, da;
    wa = wordpron;
    da = duppron;
   
    for (int i = 0; i < countSpaces(duppron) + 1; i++){ 
        len ++;
         
        splitOnSpace(wa,wb,wa);
        splitOnSpace(da,db,da);
        
        if (wb == db) {
            sim ++;
        }
        else {
            // if they're not the same start the string you're checking against with the next phoneme
            // for an added phoneme
            splitOnSpace(da,db,da);
            if (wb == db) {
                sim ++;
            }
        }
    }

    if (sim == len) {
        // check if the similarity is the same as the length
        // one was skipped on the longer pronunciation so it should be the same 
        return true;
    }
    else {
        return false;
    }

}

bool checkRemove (std::string word, std::string wordpron, std::string dup, std::string duppron) {
    int len = 0;
    int sim = 0;
    
    std::string wb, wa, db, da;
    wa = wordpron;
    da = duppron;
   
    for (int i = 0; i < countSpaces(wordpron) + 1; i++){ 
        len ++;
         
        splitOnSpace(wa,wb,wa);
        splitOnSpace(da,db,da);
        
        if (wb == db) {
            sim ++;
        }
        else {
            // if they're not the same start the string you're checking with the next phoneme
            // for a removed phoneme
            splitOnSpace(wa,wb,wa);
            if (wb == db) {
                sim ++;
            }
        }
    }

    if (sim == len) {
        // check if the similarity is the same as the length
        // one was skipped on the longer pronunciation so it should be the same 
        return true;
    }
    else {
        return false;
    }

}


int main() {
    std::string input, word, pronun, line, identical, replace, add, remove;
    std::string inputpro = "Not found";
    std::string fname = "cmudict.0.7a";
    std::cin >> input;
    
    for (int i = 0; i < input.length(); i++) {
        upper(input[i]);
    }
    
    std::ifstream fin(fname);
    while(std::getline(fin, line)) {
        // separates the word from the pronunciation
        splitOnSpace(line, word, pronun);
        
        // checks to make sure that all letters are valid (alpha or "'")
        bool val = true;
        for (int i = 0; i < word.length(); i++) {
            int c = word[i];
            if (!isalph(c)) {
                val = false;
            }
        }
        if (val && word == input) {
            inputpro = pronun;
            std::cout << "\nPronunciation    : " << pronun << "\n" << std::endl;                
        }
    }
    
    if (inputpro == "Not found") {
        std::cout << "Not found\n" << std::endl;
    }
    else {
        std::ifstream fin2(fname);
     
        while(std::getline(fin2, line)) {
            // separates the word from the pronunciation
            splitOnSpace(line, word, pronun);
            
            // checks to make sure that all letters are valid (alpha or "'")
            bool val = true;
            for (int i = 0; i < word.length(); i++) {
                int c = word[i];
                if (!isalph(c)) {
                    val = false;
                }
            } 
            
            if (val && identicalPronun(input, inputpro, word, pronun)) {
                // checks if the word is identical
                identical += word + " ";                
            }
            else if(val && countSpaces(inputpro) == countSpaces(pronun)) {
                // checks if a phoneme is replaced 
                if (checkReplace(input, inputpro, word, pronun)) {
                    replace += word + " "; 
                }
            }
            else if(val && countSpaces(inputpro)+1 == countSpaces(pronun)) {
                // checks if a phoneme is added 
                if (checkAdd(input, inputpro, word, pronun)) {
                    add += word + " "; 
                }
            }
            else if(val && countSpaces(inputpro)-1 == countSpaces(pronun)) {
                // checks if a phoneme is removed
                if (checkRemove(input, inputpro, word, pronun)) {
                    remove+= word + " "; 
                }
            }
        }

        std::cout << "Identical        : " << identical << std::endl; 
        std::cout << "Add phoneme      : " << add << std::endl;
        std::cout << "Remove phoneme   : " << remove << std::endl;
        std::cout << "Replace phoneme  : " << replace << std::endl;
    }

    return 0; 
}
