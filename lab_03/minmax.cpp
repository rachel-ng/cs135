/* 
Author: Rachel Ng 
Course: CSCI-136
Instructor: Zamansky
Assignment: Lab 3B

Prints the minimum and maximum East basin storage for the year
*/

#include <iostream> 
#include <fstream>
#include <cstdlib>
#include <climits>

int main() {
    std::ifstream fin("Current_Reservoir_Levels.tsv");
    
    if (fin.fail()) {
        std::cerr << "File cannot be opened for reading." << std::endl;
        std::exit(1); // exit if file I/O failed 
    }
    
    std::string junk; 
    std::getline(fin, junk); // reads a line 

    std::string date;
    double eastSt;
    double minsto = -1;
    double maxsto = -1;

    while(fin >> date >> eastSt) { // reads file line-by-line
        fin.ignore(INT_MAX, '\n'); // skips to end of line, ignores the rest 

        if (minsto < 0 or minsto > eastSt) {
            minsto = eastSt;
        }
        
        if (maxsto < 0 or eastSt > maxsto) {
            maxsto =  eastSt;
        }
    }

    std::cout << "minimum storage in East basin: " << minsto << std::endl;
    std::cout << "MAXimum storage in East basin: " << maxsto << std::endl;

    fin.close();

    return 0;
}
