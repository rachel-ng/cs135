/*
Author: Rachel Ng
Course: CSCI-135
Instructor: Maryash
Assignment: E9.3

Circuit
*/


#include <iostream> 

class Circuit {
public: 
    int get_first_switch_state() {
        return switch1;    
    }

    int get_second_switch_state() {
        return switch2;    
    }

    int get_lamp_state() {
        return lamp;
    }

    void toggle_first_switch() {
        if (switch1 == 0) {
            switch1 = 1;
        }
        else {
            switch1 = 0;
        }
        
        if (lamp == 0) {
            lamp = 1;
        }
        else {
            lamp = 0;
        }
    }

    void toggle_second_switch() {
        if (switch2 == 0) {
            switch2 = 1;
        }
        else {
            switch2 = 0;
        }
        
        if (lamp == 0) {
            lamp = 1;
        }
        else {
            lamp = 0;
        }
    }

private: 
    int switch1 = 0; 
    int switch2 = 0;
    int lamp;
};

