
#include <cstdlib>
#include <iostream>
#include <vector> 
#include <algorithm>
#include "bot.h"

using namespace std;

const int MAX_ROBOT_NUM = 50;
const int NEIGHBORS[8][2] = {{-1,0},{0,-1},{0,1},{1,0},{-1,-1},{-1,1},{1,-1},{1,1}};
const int ADJACENT[4][2] = {{-1,0},{0,-1},{0,1},{1,0}};
int NUM;          // to remember number or robots
int ROWS, COLS;   // map dimensions
vector<Loc> LOCATIONS;  
vector<Loc> BROKEN_LOC;  
std::vector<int> FIXERS;

/* Initialization procedure, called when the game starts: */
void onStart(int num, int rows, int cols, double mpr,
             Area &area, ostream &log)
{
	NUM = num;   // save the number of robots and the map dimensions
	ROWS = rows;
	COLS = cols;
	
    LOCATIONS.resize(NUM);
    BROKEN_LOC.resize(NUM);
    FIXERS.resize(NUM, -1);

    log << "Start!" << endl;
}

double manhattanDist(Loc start, Loc target) {
    return abs(start.c-target.c) + abs(start.r-target.r);
}

/* Deciding robot's next move */
Action onRobotAction(int id, Loc loc, Area &area, ostream &log) {
	int row = loc.r; // current row and column
	int col = loc.c;
	LOCATIONS[id] = loc;
    if (area.inspect(row, col) == DEBRIS) {
		return COLLECT;
	}
    else if (FIXERS[id] != -1) {
        int target = FIXERS[id];
        int target_r = BROKEN_LOC[target].r;
        int target_c = BROKEN_LOC[target].c;
        int next_r = row;
        int next_c = col;
        int pref_r = target_r < next_r ? -1 : 1;
        int pref_c = target_c < next_c ? -1 : 1;
        pref_r = target_r == next_r ? 0 : pref_r;
        pref_c = target_c == next_c ? 0 : pref_c;

        for (int i = 0; i < 4; i++) {
            next_r = row + ADJACENT[i][0];
            next_c = col + ADJACENT[i][1];
            next_loc = {next_r, next_c};
            if(area.inspect(next_r, next_c) == DEBRIS && (next_r - row == pref_r || next_c - col == pref_c)) {
                switch(i) {
                case 0:
                    return UP;
                case 1:
                    return LEFT;
                case 2:
                    return RIGHT;
                default:
                    return DOWN;
                } 
            }
        }
        
        switch(rand() % 1) {
		case 0:
            switch(rand() % 2) {
            case 0:
                return LEFT;
            case 1:
                return RIGHT;
            }
        case 1:
			return RIGHT;
		}

        
    }
    else {
        for (int i = 0; i < 8; i++) {
            if(area.inspect(row + NEIGHBORS[i][0], col + NEIGHBORS[i][1]) == DEBRIS) {
                switch(i) {
                case 0:
                    return UP;
                case 1:
                    return LEFT;
                case 2:
                    return RIGHT;
                case 3:
                    return DOWN;
                case 4:
                    return UP;
                case 5:
                    return UP;
                case 6:
                    return DOWN;
                default:
                    return DOWN;
                }
            }
        }

        // if not at a debris field, move randomly:
		switch(rand() % 4) {
		case 0:
			return LEFT;
		case 1:
			return RIGHT;
		case 2:
			return UP;
		default:
			return DOWN;
		}
	}
}

void onRobotMalfunction(int id, Loc loc, Area &area, ostream &log) {
	log << "Robot " << id << " is damaged." << endl;
	log << "Location: " << loc.r << ", " << loc.c << endl;
    BROKEN_LOC[id] = loc;
    int min = ROWS * COLS;
    int fix = -1;
    for (int i = 0; i < NUM; i++) {
        if (i != id && FIXERS[i] == -1) {
            if (manhattanDist(loc, LOCATIONS[i]) < min) {
                min = manhattanDist(loc, LOCATIONS[i]);
                fix = i;
            }
        }
    }
    FIXERS[fix] = id;
	log << "Robot " << fix << "to fix" << FIXERS[fix]<< endl;
}

void onClockTick(int time, ostream &log) {
	if (time % 100 == 0) log << time << " ";
}


