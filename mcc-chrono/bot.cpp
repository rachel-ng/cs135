
#include <cstdlib>
#include <iostream>
#include <vector> 
#include <cmath>
#include "bot.h"
#include "map.h"

using namespace std;

const int MAX_ROBOT_NUM = 50;
int NUM;          // to remember number or robots
int ROWS, COLS;   // map dimensions


Map map = Map(0,0,MAX_ROBOT_NUM); 
const int NEIGHBORS[12][2] = {{-1,0},{0,-1},{0,1},{1,0},{-1,-1},{-1,1},{1,-1},{1,1},{-2,0},{0,-2},{0,2},{2,0}};
const int ADJC[4][2] = {{-1,0},{0,-1},{0,1},{1,0}};

vector<Loc> BROKEN_LOC;  
std::vector<int> FIXERS;
std::vector<bool> DEAD;

bool in_range (Loc loc) {
  return (loc.r >= 0 && loc.c >= 0 && loc.r < ROWS && loc.c < COLS);
}
double manhattanDist(Loc start, Loc target) {
    return abs(start.c-target.c) + abs(start.r-target.r);
}

/* Initialization procedure, called when the game starts: */
void onStart(int num, int rows, int cols, double mpr,
             Area &area, ostream &log)
{
	NUM = num;   // save the number of robots and the map dimensions
	ROWS = rows;
	COLS = cols;

    map = Map(ROWS,COLS,NUM);
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (area.inspect(r,c) != DEBRIS) { 
                map.update({r,c},EMPT);
            }
            if (area.inspect(r,c) == DEBRIS) { 
                map.update({r,c},TRASH);
            }
        }
    }
    for (int i = 0; i < NUM; i++) {
        map.update(area.locate(i), ROBOT, i);
        //log << i << "\t" << area.locate(i).r << ", " << area.locate(i).c << endl;
    }

 
    BROKEN_LOC.resize(NUM + 1,{-1,-1});
    FIXERS.resize(NUM + 1, -1);
    DEAD.resize(NUM + 1, false);

    log << "Start!" << endl;
}

/* Deciding robot's next move */
Action onRobotAction(int id, Loc loc, Area &area, ostream &log) {
	int row = loc.r; // current row and column
	int col = loc.c;
    if (DEAD[id]) {
		return COLLECT;
    }
	if (area.inspect(row, col) == DEBRIS) {
		return COLLECT;
	}
    else if (FIXERS[id] != -1) {
        // if it's targeting a broken robot 
        int target_r = BROKEN_LOC[FIXERS[id]].r;
        int target_c = BROKEN_LOC[FIXERS[id]].c;
        int pref_r = target_r < row ? -1 : 1;
        int pref_c = target_c < col ? -1 : 1;
        pref_r = target_r == row ? 0 : pref_r;
        pref_c = target_c == col ? 0 : pref_c;

        // if it's right next to The Broken Robot 
        if (target_r == row && abs(target_c-col) == 1) {
            DEAD[FIXERS[id]] = false;
            FIXERS[id] = -1;
            //map.update({row,col + pref_c},ROBOT,1); 
            //map.update({row,col + pref_c},EMPT); 
            return pref_c == -1 ? REPAIR_LEFT : REPAIR_RIGHT; 
        }
        if (target_c == col && abs(target_r-row) == 1) {
            DEAD[FIXERS[id]] = false;
            FIXERS[id] = -1;
            //map.update({row + pref_r,col},ROBOT,1);
            //map.update({row + pref_r,col},EMPT);
            return pref_r == -1 ? REPAIR_UP : REPAIR_DOWN; 
        }
        // chooses the field with debris to move to next
        if (in_range({row + pref_r, col})) {
            if (area.inspect(row + pref_r, col) == DEBRIS) {
                return pref_r == -1 ? UP : DOWN;
            } 
        }
        if (in_range({row, col + pref_c})) {
            if (area.inspect(row, col + pref_c) == DEBRIS) {
                return pref_c == -1 ? LEFT : RIGHT;
            }
        }
        // if no debris and row or col is the same, continue moving in the direction of the broekn robot
        if (pref_r == 0) {
            return pref_c == -1 ? LEFT : RIGHT;
        }
        if (pref_c == 0) {
            return pref_r == -1 ? UP : DOWN;
        }
       
        // choose a random spot
        if (in_range({row + pref_r,col})) {
            return pref_r == -1 ? UP : DOWN;
        }
        if (in_range({row,col + pref_c})) {
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
	//BROKEN_LOC[id] = loc;
    //DEAD[id] = true;
    int min = ROWS * COLS;
    int fix = -1;
    for (int i = 0; i < NUM; i++) {
        if (i != id && FIXERS[i] == -1) {
            if (manhattanDist(loc, area.locate(i)) < min) {
                min = manhattanDist(loc, area.locate(i));
                fix = i;
            }
        }
    }
    //FIXERS[fix] = id;
	log << "Robot " << fix << " to fix " << FIXERS[fix]<< loc.r << ", " << loc.c << ")" << endl;

    log << "Robot " << id << " is damaged." << endl;
}

void onClockTick(int time, ostream &log) {
	if (time % 100 == 0) log << time << " ";
}


