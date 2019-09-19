/* 
Author: Rachel Ng 
Course: CSCI-136
Instructor: Zamansky
Assignment: Lab 3D

Takes a time range
Prints West basin's elevation for all days within the given range in reversed order
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
    std::string days [365];
    double elevations [365];
    int vals = 0;

    while(fin >> date >> eastSt >> eastEl >> westSt >> westEl) { // reads file line-by-line
        fin.ignore(INT_MAX, '\n'); // skips to end of line, ignores the rest 
        
        // creates an array with the date for easy calculations
        int day [3] = {stoi(date.substr(0,2)), stoi(date.substr(3,2)), stoi(date.substr(6,4))};
        
        if (day[0] >= starting[0] and day[0] <= ending[0] and day[2] >= starting[2] and day[2] <= ending[2]) { 
            if (day[0] > starting[0] and day[0] < ending[0]){
                days[vals] = date;
                elevations[vals] = westEl; 
                vals ++;
            }
            else if (day[0] == starting[0] and day[0] == ending[0] and day[1] >= starting[1] and day[1] <= ending[1]) {
                days[vals] = date;
                elevations[vals] = westEl; 
                vals ++;
            }
            else if (day[0] == starting[0] and day[0] != ending[0] and day[1] >= starting[1]) {
                days[vals] = date;
                elevations[vals] = westEl; 
                vals ++;
            }
            else if (day[0] == ending[0] and day[0] != starting[0] and day[1] <= ending[1]) {
                days[vals] = date;
                elevations[vals] = westEl; 
                vals ++;
            }
        }
    }

    for (int i = vals - 1; i >= 0; i--) {
        std::cout << days[i] << " " << elevations[i] << " ft" << std::endl;
    }

    fin.close();

    return 0;
}
