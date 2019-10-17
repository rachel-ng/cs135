/* 
Author: Rachel Ng 
Course: CSCI-135
Instructor: Maryash
Assignment: Project 2

Pronunciation dictionary
*/


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <climits>

void upper(char & a){
    int c = a;
    if (c > 96 && c < 123 && c != 39){
        a = (char)c - 32;
    }
}

bool isalph(char c) {
    if ((c > 64 && c < 91) || (c > 96 && c < 123)) {
        return true;
    }
    if (c == 39) {
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
            spaces += 1;
        }
    }
    return spaces;
}

bool identicalPronun (std::string word, std::string wordpron, std::string dup, std::string duppron) {
    if (wordpron == duppron && word != dup) {
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
        //std::cout << wb << "\t" << db << std::endl;
        if (wb == db) {
            sim ++;
        }
        //std::cout << i << std::endl;
    }

    if (sim == len - 1) {
        //std::cout << word << "\n" << dup << "\n" << std::endl;
        //std::cout << wordpron << "\t" << countSpaces(duppron)<< "\n" << duppron << "\t" << countSpaces(duppron)<< "\n" << std::endl;
        //std::cout << sim << "\n" << len << "\n" << std::endl;
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
        //std::cout << wb << "\t" << db << std::endl;
        if (wb == db) {
            sim ++;
        }
        else {
            splitOnSpace(da,db,da);
            if (wb == db) {
                sim ++;
            }
        }
        //std::cout << i << std::endl;
    }

    if (sim == len) {
        //std::cout << word << "\n" << dup << "\n" << std::endl;
        //std::cout << wordpron << "\t" << countSpaces(duppron)<< "\n" << duppron << "\t" << countSpaces(duppron)<< "\n" << std::endl;
        //std::cout << sim << "\n" << len << "\n" << std::endl;
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
        //std::cout << wb << "\t" << db << std::endl;
        if (wb == db) {
            sim ++;
        }
        else {
            splitOnSpace(wa,wb,wa);
            if (wb == db) {
                sim ++;
            }
        }
        //std::cout << i << std::endl;
    }

    if (sim == len) {
        //std::cout << word << "\n" << dup << "\n" << std::endl;
        //std::cout << wordpron << "\t" << countSpaces(duppron)<< "\n" << duppron << "\t" << countSpaces(duppron)<< "\n" << std::endl;
        //std::cout << sim << "\n" << len << "\n" << std::endl;
        return true;
    }
    else {
        return false;
    }

}


int main() {

    std::string input, inputpro, identical, replace, add;
    std::cin >> input;
    
    for (int i = 0; i < input.length(); i++) {
        upper(input[i]);
    }

    std::ifstream fin("cmudict.0.7a.txt");
    
    std::string line, word, pronun, remove; 
    
    while(std::getline(fin, line)) {
        splitOnSpace(line, word, pronun);
        bool val = true;
        for (int i = 0; i < word.length(); i++) {
            int c = word[i];
            if (!isalph(c)) {
                val = false;
                if(word[0] == 'P') {
                    std::cout << word << std::endl;
                }
            }
        }
        if (val && word == input) {
            inputpro = pronun;
            // std::cout << word << std::endl;
            std::cout << "\nPronunciation\t: " << pronun << "\n" << std::endl;                
        }
    }
    if (inputpro == "") {
        std::cout << "Ding dong your input is wrong, try again." << std::endl;
    }

    std::ifstream fin2("cmudict.0.7a.txt");
 
    while(std::getline(fin2, line)) {
        splitOnSpace(line, word, pronun);
        bool val = true;
        for (int i = 0; i < word.length(); i++) {
            int c = word[i];
            if (!isalph(c)) {
                val = false;
            }
        } 
        if (val && identicalPronun(input, inputpro, word, pronun)) {
            identical += word + " ";                
        }
        else if(val && countSpaces(inputpro) == countSpaces(pronun)) {
            if (checkReplace(input, inputpro, word, pronun)) {
                replace += word + " "; 
            }
        }
        else if(val && countSpaces(inputpro)+1 == countSpaces(pronun)) {
            if (checkAdd(input, inputpro, word, pronun)) {
                add += word + " "; 
            }
        }
        else if(val && countSpaces(inputpro)-1 == countSpaces(pronun)) {
            if (checkRemove(input, inputpro, word, pronun)) {
                remove+= word + " "; 
            }
        }
    }
    
    std::cout << "Identical\t: " << identical << std::endl; 
    std::cout << "Add phoneme\t: " << add << std::endl;
    std::cout << "Remove phoneme\t: " << remove << std::endl;
    std::cout << "Replace phoneme\t: " << replace << std::endl;
    std::cout << std::endl;
   

    return 0; 
}
