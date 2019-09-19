/* 
Author: Rachel Ng 
Course: CSCI-136
Instructor: Zamansky
Assignment: Lab 3A

Takes a date in MM/DD/YYYY format
Prints the East basin storage on that day
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

    std::string requested_date;
    std::cout << "Enter date: ";
    std::cin >> requested_date;

    std::string date;
    double eastSt;

    while(fin >> date >> eastSt) { // reads file line-by-line
        fin.ignore(INT_MAX, '\n'); // skips to end of line, ignores the rest 

        if (date == requested_date) { 
            std::cout << "East basin storage: " <<  eastSt << " billion gallons" << std::endl;
        }
    }
    
    fin.close();

    return 0;
}
