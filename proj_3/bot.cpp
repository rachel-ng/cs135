
#include <cstdlib>
#include <iostream>
#include <vector> 
#include <cmath>
#include "bot.h"

using namespace std;

const int MAX_ROBOT_NUM = 50;
int NUM;
int ROWS, COLS;

int BOUND_R = 0;
int BOUND_C = 0;

const int NEIGHBORS[12][2] = {{-1,0},{0,-1},{0,1},{1,0},{-1,-1},{-1,1},{1,-1},{1,1},{-2,0},{0,-2},{0,2},{2,0}};
const int ADJC[4][2] = {{-1,0},{0,-1},{0,1},{1,0}};

vector<Loc> LOCATIONS;  
vector<Loc> BROKEN_LOC;  
std::vector<int> FIXERS;
std::vector<std::vector<int>> TREAD;
std::vector<std::vector<int>> DEAD;


bool in_range (Loc loc) {
  return (loc.r >= BOUND_R && loc.c >= BOUND_C && loc.r < ROWS && loc.c < COLS);
}

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
        else if (in_range({row + NEIGHBORS[i][0],col + NEIGHBORS[i][1]})) {
            DEAD[row + NEIGHBORS[i][0]][col + NEIGHBORS[i][1]] += 1;
        }
    }
    return yeet;
}

void bounds(Area &area) {
    std::vector<bool> all_ded_c;
    all_ded_c.resize(COLS, true);
    std::vector<bool> all_ded_r;
    all_ded_r.resize(ROWS, true);
    for (int r = BOUND_R; r < ROWS; r++) {
        for (int c = BOUND_C; c < COLS; c++) {
            int t = TREAD[r][c] > 0 ? 1 : 0; 
            int d = DEAD[r][c] > 0 ? 1 : 0; 
            int a = (t == 0 && d == 0) ? ((area.inspect(r,c) == EMPTY) ? 1 : 0) : 1;
            if (a > 0) {
                DEAD[r][c] += 1;
            }
            all_ded_r[r] = (t > 0 && d > 0 && a > 0) ? all_ded_r[r] : false;
            all_ded_c[c] = (t > 0 && d > 0 && a > 0) ? all_ded_c[c] : false;
        }
    }
    for (int i = BOUND_C + 1; i < COLS; i++) {
        if (!all_ded_c[i]) {
            BOUND_C = i - 1;
            break;
        }
    }
    for (int i = BOUND_R + 1; i < ROWS; i++) {
        if (!all_ded_r[i]) {
            BOUND_R = i - 1;
            break;
        }
    }
}

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
    DEAD.resize(ROWS, std::vector<int>(COLS, 0));
	bounds(area);
    log << "Start!" << endl;
}
/* Deciding robot's next move */
Action onRobotAction(int id, Loc loc, Area &area, ostream &log) {
	bounds(area);
    int row = loc.r; 
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
	    bounds(area);
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
            else if (in_range({row + NEIGHBORS[i][0],col + NEIGHBORS[i][1]})) {
                DEAD[row + NEIGHBORS[i][0]][col + NEIGHBORS[i][1]] += 1;
            }
        }
        
        int best = -1;
        int bestv = ROWS * COLS;
        for (int i = 0; i < 4; i++) {
            if (in_range({row + ADJC[i][0],col + ADJC[i][1]})) {
                best = TREAD[row + ADJC[i][0]][col + ADJC[i][1]] < bestv ? i : best;
                bestv = TREAD[row + ADJC[i][0]][col + ADJC[i][1]] < bestv ? TREAD[row + ADJC[i][0]][col + ADJC[i][1]] : bestv;
            }
            else if (row+ADJC[i][0] <= BOUND_R) {
                return DOWN;
            }
            else if (row+ADJC[i][0] == ROWS - 1) {
                return UP;
            }
            else if (row+ADJC[i][1] <= BOUND_C) {
                return RIGHT;
            }
        }

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
	log << "Robot " << fix << " to fix " << FIXERS[fix]<< loc.r << ", " << loc.c << ")" << endl;
}

void onClockTick(int time, ostream &log) {
	if (time % 100 == 0) {
        log << time << "\t" << BOUND_R << ", " << BOUND_C<< endl;
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


