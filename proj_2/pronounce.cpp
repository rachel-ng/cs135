#include <iostream>
#include <fstream>
#include <cstdlib>
#include <climits>

void upper(char & a){
    int c = a;
    if (c > 96 && c < 123){
        a = (char)c - 32;
    }
}

bool isalpha(char c) {
    if ((c > 64 && c < 91) || (c > 96 && c < 123) || c == 39) {
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
    return false;
}

int main() {

    std::string input, inputpro, identical, replace, add;
    std::cin >> input;
    
    for (int i = 0; i < input.length(); i++) {
        upper(input[i]);
    }

    std::ifstream fin("cmudict.0.7a.txt");
    
    std::string line, word, pronun; 
    
    while(std::getline(fin, line)) {
        splitOnSpace(line, word, pronun);
        bool val = true;
        for (int i = 0; i < word.length(); i++) {
            int c = word[i];
            //if (!(c == 39 || c > 64 || (c > 90 && c < 97) || c > 122)) {
            if (!isalpha(c)) {
                val = false;
            }
        }
        if (val && word == input) {
            inputpro = pronun;
            std::cout << word << std::endl;
            std::cout << "Pronunciation\t: " << pronun << std::endl;                
        }
    }
    if (inputpro == "") {
        std::cout << "Not found" << std::endl;
    }

    fin.close();

    std::ifstream fin2("cmudict.0.7a.txt");
 
    while(std::getline(fin2, line)) {
        splitOnSpace(line, word, pronun);
        bool val = true;
        for (int i = 0; i < word.length(); i++) {
            int c = word[i];
            //if (!(c == 39 || c > 64 || (c > 90 && c < 97) || c > 122)) {
            if (!isalpha(c)) {
                val = false;
            }
        } 
        if (val && identicalPronun(input, inputpro, word, pronun)) {
            identical += word + " ";                
        }
        else if(val && countSpaces(inputpro) == countSpaces(pronun)) {
            if (checkReplace(input, inputpro, word, pronun)) {
                replace += word + " (" + pronun + ") ";
            }
        }
    }
    std::cout << "Identical\t: " << identical << std::endl; 
    std::cout << "Replace phoneme\t: " << replace << std::endl;
    std::cout << std::endl;
   

    return 0; 
}
