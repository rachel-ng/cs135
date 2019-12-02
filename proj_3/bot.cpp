
#include <cstdlib>
#include <iostream>
#include <vector> 
#include <cmath>
#include "bot.h"
#include "map.h"

using namespace std;

const int MAX_ROBOT_NUM = 50;
int NUM;
int ROWS, COLS;

Map map = Map(0,0,MAX_ROBOT_NUM); 

const int NEIGHBORS[12][2] = {{-1,0},{0,-1},{0,1},{1,0},{-1,-1},{-1,1},{1,-1},{1,1},{-2,0},{0,-2},{0,2},{2,0}};
const int ADJC[4][2] = {{-1,0},{0,-1},{0,1},{1,0}};

vector<Loc> BROKEN_LOC;  
std::vector<int> FIXERS;

double manhattanDist(Loc start, Loc target) {
    return abs(start.c-target.c) + abs(start.r-target.r);
}

int check_kernel (Area &area, Loc loc) {
    int yeet = 0;
    int row = loc.r; 
	int col = loc.c;

    for (int i = 0; i < 12; i++) {
        if(area.inspect(row + NEIGHBORS[i][0], col + NEIGHBORS[i][1]) == DEBRIS) {
            yeet += 1;
        }
    }
    return yeet;
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

    BROKEN_LOC.resize(NUM);
    FIXERS.resize(NUM, -1);
	
    log << "Start!" << endl;
}

/* Deciding robot's next move */
Action onRobotAction(int id, Loc loc, Area &area, ostream &log) {
    int row = loc.r; 
	int col = loc.c;
    if (area.locate(id).r != map.locate(id).r && area.locate(id).c != map.locate(id).c) {
        log << id << endl;
        log << area.locate(id).r << ", " <<area.locate(id).c << "\t" << map.locate(id).r << ", " << map.locate(id).c << endl;
        log << area.inspect(area.locate(id)) << "\t" << area.inspect(map.locate(id)) << endl;
        log << map.peek(area.locate(id)).status << "\t" << map.peek(map.locate(id)).status << endl; 
    } 
    map.update(loc,EMPT);
    if (area.inspect(row, col) == DEBRIS) {
        map.update(loc,ROBOT,id);
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
            map.update({row,col + pref_c},ROBOT,FIXERS[id]);
            FIXERS[id] = -1;
            return pref_c == -1 ? REPAIR_LEFT : REPAIR_RIGHT; 
        }
        if (target_c == col && abs(target_r-row) == 1) {
            map.update({row + pref_r,col},ROBOT,FIXERS[id]);
            FIXERS[id] = -1;
            return pref_r == -1 ? REPAIR_UP : REPAIR_DOWN; 
        }

        // chooses the field with debris to move to next
        if (area.inspect(row + pref_r, col) == DEBRIS) {
            map.update({row + pref_r,col},ROBOT,id);
            return pref_r == -1 ? UP : DOWN;
        }
        if (area.inspect(row, col + pref_c) == DEBRIS) {
            map.update({row,col + pref_c},ROBOT,id);
            return pref_c == -1 ? LEFT : RIGHT;
        }

        // if no debris and row or col is the same, continue moving in the direction of the broekn robot
        if (pref_r == 0) {
            map.update({row,col + pref_c},ROBOT,id);
            return pref_c == -1 ? LEFT : RIGHT;
        }
        if (pref_c == 0) {
            map.update({row + pref_r,col},ROBOT,id);
            return pref_r == -1 ? UP : DOWN;
        }
        
        // choose a random spot
        switch(rand() % 1) {
		case 0:
            map.update({row + pref_r,col},ROBOT,id);
            return pref_r == -1 ? UP : DOWN;
        default:
            map.update({row,col + pref_c},ROBOT,id);
            return pref_c == -1 ? LEFT : RIGHT;
		}
    }
    else {
        // if it's next to a debris field
        for (int i = 0; i < 12; i++) {
            if(area.inspect(row + NEIGHBORS[i][0], col + NEIGHBORS[i][1]) == DEBRIS) {
                map.update({row + NEIGHBORS[i][0],col + NEIGHBORS[i][1]},ROBOT,id);
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
            else if (map.peek(row + NEIGHBORS[i][0], col + NEIGHBORS[i][1]).status == ROBOT) {
               map.treaded({row + NEIGHBORS[i][0], col + NEIGHBORS[i][1]}); 
               //map.treaded({row + NEIGHBORS[i][0], col + NEIGHBORS[i][1]}); 
            }
        }
        
        // if it's out of bounds it continues to move until it's no longer out of bounds

        if (row <= map.b_r() && map.in_range({map.b_r() + 1,col})) {
            map.update({row+1,col},ROBOT,id);
            return DOWN;
        }
        if (row >= map.b_rb() && map.in_range({map.b_rb() - 1,col})) {
            map.update({row-1,col},ROBOT,id);
            return UP;
        }
        if (col <= map.b_c() && map.in_range({row,map.b_c() + 1})) {
            map.update({row,col+1},ROBOT,id);
            return RIGHT;
        }
        if (col >= map.b_cb() && map.in_range({row,map.b_cb() - 1})) {
            map.update({row,col-1},ROBOT,id);
            return LEFT;
        }

        // choose the least treaded on field

        int best = -1;
        int bestv = ROWS * COLS;
        for (int i = 0; i < 4; i++) {
            if (map.in_range({row + ADJC[i][0],col + ADJC[i][1]})) {
                best = map.tread({row + ADJC[i][0],col + ADJC[i][1]}) < bestv ? i : best;
                bestv =  map.tread({row + ADJC[i][0],col + ADJC[i][1]}) < bestv ? map.tread({row + ADJC[i][0],col + ADJC[i][1]}) : bestv;
            }
            else if (row+ADJC[i][0] <= map.b_r()-1) {
                map.update({row+1,col},ROBOT,id);
                return DOWN;
            }
            else if (row+ADJC[i][0] >= map.b_rb()+1) {
                map.update({row-1,col},ROBOT,id);
                return UP;
            }
            else if (col+ADJC[i][1] <= map.b_c()-1) {
                map.update({row,col+1},ROBOT,id);
                return RIGHT;
            }
            else if (col+ADJC[i][1] >= map.b_cb()+1) {
                map.update({row,col-1},ROBOT,id);
                return LEFT;
            }
        }

        //log << bestv << "\t" << map.tread({row + ADJC[best][0],col + ADJC[best][1]}) << endl; 
        
        map.update({row + ADJC[best][0],col + ADJC[best][1]},ROBOT,id);
        
        switch(best) {
		case 0: return UP;
		case 1: return LEFT;
		case 2: return RIGHT;
		default: return DOWN;
		}
	}
}

void onRobotMalfunction(int id, Loc loc, Area &area, ostream &log) {
	//log << "Robot " << id << " is damaged (" << loc.r << ", " << loc.c << ")" << endl;
    BROKEN_LOC[id] = loc;
    map.update(loc,DED,id);
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
    FIXERS[fix] = id;
	log << "Robot " << fix << " to fix " << FIXERS[fix]<< loc.r << ", " << loc.c << ")" << endl;
}

void onClockTick(int time, ostream &log) {
	if (time % 100 == 0) {
        log << time << "\t" << map.b_r() << ", " << map.b_c() << "\t" << map.b_rb() << ", " << map.b_cb()<< "\t" <<  map.clear() << " / " << map.pile() << "\t" << NUM << endl;
    }
}


