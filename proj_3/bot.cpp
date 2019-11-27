
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
int BOUND_R = 0;
int BOUND_C = 0;

Map map = {0,0,MAX_ROBOT_NUM};

const int NEIGHBORS[12][2] = {{-1,0},{0,-1},{0,1},{1,0},{-1,-1},{-1,1},{1,-1},{1,1},{-2,0},{0,-2},{0,2},{2,0}};
const int ADJC[4][2] = {{-1,0},{0,-1},{0,1},{1,0}};
int CORNERS[4][2];
int CORNER = 0;

vector<Loc> BROKEN_LOC;  
std::vector<int> FIXERS;
std::vector<int> CHECKERS;

bool in_range (Loc loc) {
  return (loc.r >= BOUND_R && loc.c >= BOUND_C && loc.r < ROWS && loc.c < COLS);
}

double manhattanDist(Loc start, Loc target) {
    return abs(start.c-target.c) + abs(start.r-target.r);
}

/*int check_kernel (Area &area, Loc loc) {
    int yeet = 0;
    int row = loc.r; 
	int col = loc.c;

    for (int i = 0; i < 12; i++) {
        if(area.inspect(row + NEIGHBORS[i][0], col + NEIGHBORS[i][1]) == TRASH) {
            yeet += 1;
        }
        else if (in_range({row + NEIGHBORS[i][0],col + NEIGHBORS[i][1]})) {
            //DEAD[row + NEIGHBORS[i][0]][col + NEIGHBORS[i][1]] += 1;
        }
    }
    return yeet;
}
void bounds(Area &area) {
    std::vector<bool> all_ded_c;
    all_ded_c.resize(COLS, true);
    for (int r = BOUND_R; r < ROWS; r++) {
        bool all_ded_r = true;
        for (int c = BOUND_C; c < COLS; c++) {
            int t = TREAD[r][c] > 0 ? 1 : 0; 
            int d = DEAD[r][c] > 0 ? 1 : 0; 
            int a = (t == 0 && d == 0) ? ((area.inspect(r,c) == EMPTY) ? 1 : 0) : 1;
            if (a > 0) {
                DEAD[r][c] += 1;
            }
            all_ded_r = (t > 0 && d > 0 && a > 0) ? all_ded_r : false;
            all_ded_c[c] = (t > 0 && d > 0 && a > 0) ? all_ded_c[c] : false;
        }
        BOUND_R = (all_ded_r && r == BOUND_R + 1) ? r : BOUND_R; 
    }
    for (int i = BOUND_C + 1; i < COLS; i++) {
        if (!all_ded_c[i]) {
            BOUND_C = i - 1;
            break;
        }
    }
}
*/
/* Initialization procedure, called when the game starts: */
void onStart(int num, int rows, int cols, double mpr,
             Area &area, ostream &log)
{
	NUM = num;   // save the number of robots and the map dimensions
	ROWS = rows;
	COLS = cols;
    
    map = {ROWS, COLS, NUM}; 

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (area.inspect(r,c) == EMPTY) { 
                map.update({r,c},EMPT);
            }
            if (area.inspect(r,c) == DEBRIS) { 
                map.update({r,c},TRASH);
            }
        }
    }
    for (int i = 0; i < NUM; i++) {
        map.update(area.locate(i), ROBOT);
    }

    //LOCATIONS.resize(NUM);
    BROKEN_LOC.resize(NUM);
    FIXERS.resize(NUM, -1);
    CHECKERS.resize(NUM, -1);
    //TREAD.resize(ROWS, std::vector<int>(COLS, 0));
    //DEAD.resize(ROWS, std::vector<int>(COLS, 0));
    //CORNERS = {{0,0},{0,COLS-1},{ROWS-1,0},{ROWS-1,COLS-1}};
    /*int min = ROWS * COLS;
    int fix = -1;
    for (int i = 0; i < NUM; i++) {
        if (manhattanDist(CORNERS[CORNER], LOCATIONS[i]) < min) {
            min = manhattanDist(CORNERS[CORNER], LOCATIONS[i]);
            fix = i;
        }
    }
    CHECKERS[fix] = 1;
    */
    log << "Start!" << endl;
}
/* Deciding robot's next move */
Action onRobotAction(int id, Loc loc, Area &area, ostream &log) {
    int row = loc.r; 
	int col = loc.c;
	
    map.update({row,col},EMPT);

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
            map.update({row,col + pref_c},ROBOT);
            return pref_c == -1 ? REPAIR_LEFT : REPAIR_RIGHT; 
        }
        if (target_c == col && abs(target_r-row) == 1) {
            FIXERS[id] = -1;
            map.update({row + pref_r,col},ROBOT);
            return pref_r == -1 ? REPAIR_UP : REPAIR_DOWN; 
        }

        if (area.inspect(row + pref_r, col) == DEBRIS) {
            map.update({row + pref_r,col},ROBOT);
            return pref_r == -1 ? UP : DOWN;
        }
        if (area.inspect(row, col + pref_c) == DEBRIS) {
            map.update({row,col + pref_c},ROBOT);
            return pref_c == -1 ? LEFT : RIGHT;
        }

        if (pref_r == 0) {
            map.update({row,col + pref_c},ROBOT);
            return pref_c == -1 ? LEFT : RIGHT;
        }
        if (pref_c == 0) {
            map.update({row + pref_r,col},ROBOT);
            return pref_r == -1 ? UP : DOWN;
        }
        
        switch(rand() % 1) {
		case 0:
            map.update({row + pref_r,col},ROBOT);
            return pref_r == -1 ? UP : DOWN;
        default:
            map.update({row,col + pref_c},ROBOT);
            return pref_c == -1 ? LEFT : RIGHT;
		}
    }
    else {
	    //bounds(area);
        
        for (int i = 0; i < 12; i++) {
            if(area.inspect(row + NEIGHBORS[i][0], col + NEIGHBORS[i][1]) == DEBRIS) {
                map.update({row + NEIGHBORS[i][0],col + NEIGHBORS[i][1]},ROBOT);
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
//            else if (in_range({row + NEIGHBORS[i][0],col + NEIGHBORS[i][1]})) {
//                DEAD[row + NEIGHBORS[i][0]][col + NEIGHBORS[i][1]] += 1;
//            }
        }
        
        int best = -1;
        int bestv = ROWS * COLS;
        for (int i = 0; i < 4; i++) {
            if (in_range({row + ADJC[i][0],col + ADJC[i][1]})) {
                best = map.tread({row + ADJC[i][0],col + ADJC[i][1]}) < bestv ? i : best;
                bestv =  map.tread({row + ADJC[i][0],col + ADJC[i][1]}) < bestv ? map.tread({row + ADJC[i][0],col + ADJC[i][1]}) : bestv;
            }
            else if (row+ADJC[i][0] <= BOUND_R) {
                map.update({row+1,col},ROBOT);
                return DOWN;
            }
            else if (row+ADJC[i][0] == ROWS - 1) {
                map.update({row-1,col},ROBOT);
                return UP;
            }
            else if (row+ADJC[i][1] <= BOUND_C) {
                map.update({row,col+1},ROBOT);
                return RIGHT;
            }
        }
        map.update({row + ADJC[best][0],col + ADJC[best][1]},ROBOT);

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
    map.update(loc, DEAD);
    int min = ROWS * COLS;
    int fix = -1;
    for (int i = 0; i < NUM; i++) {
        if (i != id && FIXERS[i] == -1) {
            if (manhattanDist(loc, map.locate(id)) < min) {
                min = manhattanDist(loc, map.locate(id));
                fix = i;
            }
        }
    }
    FIXERS[fix] = id;
	log << "Robot " << fix << " to fix " << FIXERS[fix]<< loc.r << ", " << loc.c << ")" << endl;
}

void onClockTick(int time, ostream &log) {
	if (time % 100 == 0) {
        log << time << "\t" << BOUND_R << ", " << BOUND_C << "\n" << endl;
        //for (int i = 0; i < 4; i++) {
        //   log << SECTIONS[i] << "\t"; 
        //}
        log << endl;
        /*for (int i = 0; i < LOCATIONS.size(); i++) {
            log << i << "  " << in_sector(LOCATIONS[i].r,LOCATIONS[i].c) << "\t"; 
            if (i % 4 == 3) {
                log << endl;
            }
        }*/
    }
}


