/* 
Author: Rachel Ng 
Course: CSCI-136
Instructor: Zamansky
Assignment: Lab 3C

Takes a time range
Prints the storage basin with higher elevation within the given range
*/

#include <iostream> 
#include <fstream>
#include <cstdlib>
#include <climits>

std::string comp(double east, double west){
    // string with the basin with higher elevation 
    if (east == west) {
        return "Equal";
    }
    if (east > west) {
        return "East"; 
    }
    else {
        return "West";
    }
}

int main() {
    std::ifstream fin("Current_Reservoir_Levels.tsv");
    
    if (fin.fail()) {
        std::cerr << "File cannot be opened for reading." << std::endl;
        std::exit(1); // exit if file I/O failed 
    }
    
    std::string junk; 
    std::getline(fin, junk); // reads a line 

    std::string start, end;
    std::cout << "Enter starting date: ";
    std::cin >> start;
    std::cout << "Enter ending date: ";
    std::cin >> end;

    // creates an array with the date for easy calculations   
    int starting [3] = {stoi(start.substr(0,2)), stoi(start.substr(3,2)), stoi(start.substr(6,4))};  
    int ending [3] = {stoi(end.substr(0,2)), stoi(end.substr(3,2)), stoi(end.substr(6,4))}; 

    std::string date;
    double eastSt, eastEl, westSt, westEl;
    
    while(fin >> date >> eastSt >> eastEl >> westSt >> westEl) { // reads file line-by-line
        fin.ignore(INT_MAX, '\n'); // skips to end of line, ignores the rest 
        
        // creates an array with the date for easy calculations
        int day [3] = {stoi(date.substr(0,2)), stoi(date.substr(3,2)), stoi(date.substr(6,4))};
        
        if (day[0] >= starting[0] and day[0] <= ending[0] and day[2] >= starting[2] and day[2] <= ending[2]) { 
            if (day[0] > starting[0] and day[0] < ending[0]){
                std::cout << date << " " << comp(eastEl, westEl) << std::endl;            
            }
            else if (day[0] == starting[0] and day[0] == ending[0] and day[1] >= starting[1] and day[1] <= ending[1]) {
                std::cout << date << " " << comp(eastEl, westEl)  << std::endl;            
            }
            else if (day[0] == starting[0] and day[0] != ending[0] and day[1] >= starting[1]) {
                std::cout << date << " " << comp(eastEl, westEl) << std::endl;            
            }
            else if (day[0] == ending[0] and day[0] != starting[0] and day[1] <= ending[1]) {
                std::cout << date << " " << comp(eastEl, westEl) << std::endl;            
            }
        }
    }

    fin.close();

    return 0;
}
