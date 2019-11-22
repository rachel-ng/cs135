
#include <cstdlib>
#include <iostream>
#include <vector> 
#include <algorithm>
#include "bot.h"

using namespace std;

const int MAX_ROBOT_NUM = 50;
int NUM;          // to remember number or robots
int ROWS, COLS;   // map dimensions

//const int NEIGHBORS[8][2] = {{-1,0},{0,-1},{0,1},{1,0},{-1,-1},{-1,1},{1,-1},{1,1}};
const int NEIGHBORS[12][2] = {{-1,0},{0,-1},{0,1},{1,0},{-1,-1},{-1,1},{1,-1},{1,1},{-2,0},{0,-2},{0,2},{2,0}};
const int ADJACENT[4][2] = {{-1,0},{0,-1},{0,1},{1,0}};

vector<Loc> LOCATIONS;  
vector<Loc> BROKEN_LOC;  
std::vector<int> FIXERS;
std::vector<std::vector<int>> TREAD;

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
    TREAD.resize(ROWS, std::vector<int>(COLS, 0));
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
    TREAD[row][col] += 1;

    if (area.inspect(row, col) == DEBRIS) {
		return COLLECT;
	}
    else if (FIXERS[id] != -1) {
        int target_r = BROKEN_LOC[FIXERS[id]].r;
        int target_c = BROKEN_LOC[FIXERS[id]].c;
        int pref_r = target_r < row ? -1 : 1;
        int pref_c = target_c < col ? -1 : 1;
        pref_r = target_r == row ? 0 : pref_r;
        pref_c = target_c == col ? 0 : pref_c;

        if (target_r == row && abs(target_c-col) == 1) {
            FIXERS[id] = -1;
            return pref_c == -1 ? REPAIR_LEFT : REPAIR_RIGHT; 
        }
        if (target_c == col && abs(target_r-row) == 1) {
            FIXERS[id] = -1;
            return pref_r == -1 ? REPAIR_UP : REPAIR_DOWN; 
        }

        if (area.inspect(row + pref_r, col) == DEBRIS) {
            return pref_r == -1 ? UP : DOWN;
        }
        if (area.inspect(row, col + pref_c) == DEBRIS) {
            return pref_c == -1 ? LEFT : RIGHT;
        }

        if (pref_r == 0) {
            return pref_c == -1 ? LEFT : RIGHT;
        }
        if (pref_c == 0) {
            return pref_r == -1 ? UP : DOWN;
        }
        
        switch(rand() % 1) {
		case 0:
            return pref_r == -1 ? UP : DOWN;
        default:
            return pref_c == -1 ? LEFT : RIGHT;
		}
    }
    else {
        for (int i = 0; i < 12; i++) {
            if(area.inspect(row + NEIGHBORS[i][0], col + NEIGHBORS[i][1]) == DEBRIS) {
                switch(i) {
                case 0: return UP;
                case 1: return LEFT;
                case 2: return RIGHT;
                case 3: return DOWN;
                case 4: return UP;
                case 5: return UP;
                case 6: return DOWN;
                case 7: return DOWN;
                case 8: return UP;
                case 9: return LEFT;
                case 10: return RIGHT;
                default: return DOWN;
                }
            }
        }
        
        int best = -1;
        int bestv = ROWS * COLS;
        for (int i = 0; i < 4; i++) {
            if (row + ADJACENT[i][0] > -1 && row + ADJACENT[i][0] < ROWS && col + ADJACENT[i][1] > -1 && col + ADJACENT[i][1] < COLS) {
                best = TREAD[row + ADJACENT[i][0]][col + ADJACENT[i][1]] < bestv ? i : best;
                bestv = TREAD[row + ADJACENT[i][0]][col + ADJACENT[i][1]] < bestv ? TREAD[row + ADJACENT[i][0]][col + ADJACENT[i][1]] : bestv;
            }
        }

        // if not at a debris field, move randomly:
        switch(rand() % 4) {
		case 0: return LEFT;
		case 1: return RIGHT;
		case 2: return UP;
		default: return DOWN;
		}
	}
}

void onRobotMalfunction(int id, Loc loc, Area &area, ostream &log) {
	log << "Robot " << id << " is damaged (" << loc.r << ", " << loc.c << ")" << endl;
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
	log << "Robot " << fix << " to fix " << FIXERS[fix]<< endl;
}

void onClockTick(int time, ostream &log) {
	if (time % 100 == 0) log << time << " ";
}


