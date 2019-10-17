#include <iostream>

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
        std::cout << s[i];
        if (isspace(s[i])) {
            spaces += 1;
        }
    }
    return spaces;
}

bool checkReplace (std::string word, std::string wordpron, std::string dup, std::string duppron) {
    int len = 0;
    int sim = 0;
    
    std::string wb, wa, db, da;
    wa = wordpron;
    da = duppron;
   
    for (int i = 0; i < word.length(); i++){ 
        len ++;
        
        splitOnSpace(wa,wb,wa);
        splitOnSpace(da,db,da);
        std::cout << word << "\t\t" << wb << "\t" << wa << std::endl;
        std::cout << dup << "\t\t" << db << "\t" << da << std::endl;
        if (wb == db) {
            sim ++;
        }
    }

    std::cout << len << std::endl;
    std::cout << sim << std::endl;
    std::cout << countSpaces(wordpron) << std::endl;
    std::cout << countSpaces(duppron) << std::endl;
    if (sim == len - 1) {
        return true;
    }
    else {
        return false;
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

int main() {
    checkReplace("PLANTS","P L AE1 N T S","PLANTER","P L AE1 N T ER0");
    
    std::cout << isalpha('A') << std::endl;
    std::cout << isalpha('B') << std::endl;
    std::cout << isalpha('C') << std::endl;
    std::cout << isalpha('a') << std::endl;
    std::cout << isalpha('4') << std::endl;
    std::cout << isalpha('1') << std::endl;
    std::cout << isalpha(')') << std::endl;
    std::cout << isalpha('>') << std::endl;
    return 0;
}
