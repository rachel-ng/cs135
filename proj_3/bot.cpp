
#include <cstdlib>
#include <iostream>
#include <vector> 
#include <cmath>
#include "bot.h"

using namespace std;

const int MAX_ROBOT_NUM = 50;
int NUM;          // to remember number or robots
int ROWS, COLS;   // map dimensions

int HEIGHT, WIDTH;
int SECTORS;
//const int NEIGHBORS[8][2] = {{-1,0},{0,-1},{0,1},{1,0},{-1,-1},{-1,1},{1,-1},{1,1}};
const int NEIGHBORS[12][2] = {{-1,0},{0,-1},{0,1},{1,0},{-1,-1},{-1,1},{1,-1},{1,1},{-2,0},{0,-2},{0,2},{2,0}};
const int ADJACENT[4][2] = {{-1,0},{0,-1},{0,1},{1,0}};
int SECTIONS[4] = {0,0,0,0};
int FARTHEST[4][2] = {{0,0}, {0,2},{2,0},{2,2}};

vector<Loc> LOCATIONS;  
vector<Loc> BROKEN_LOC;  
std::vector<int> FIXERS;
std::vector<int> MOVE_TO;
std::vector<int> OPEN_SECTS = {0,1,2,3};
std::vector<std::vector<int>> TREAD;
std::vector<std::vector<int>> DEAD;

/* Initialization procedure, called when the game starts: */
void onStart(int num, int rows, int cols, double mpr,
             Area &area, ostream &log)
{
	NUM = num;   // save the number of robots and the map dimensions
	ROWS = rows;
	COLS = cols;
    SECTORS = 4;
    WIDTH = COLS / (SECTORS / 2);
    HEIGHT = ROWS / (SECTORS / 2);
    LOCATIONS.resize(NUM);
    BROKEN_LOC.resize(NUM);
    FIXERS.resize(NUM, -1);
    MOVE_TO.resize(NUM, -1);
    TREAD.resize(ROWS, std::vector<int>(COLS, 0));
    DEAD.resize(ROWS, std::vector<int>(COLS, 0));
    
    for (int i = 0; i < 4; i++) {
        FARTHEST[i][0] = abs((FARTHEST[i][0] * HEIGHT) - (HEIGHT / 2));
        FARTHEST[i][1] = abs((FARTHEST[i][0] * WIDTH) - (WIDTH / 2));
    }

    log << "Start!" << endl;
}


double manhattanDist(Loc start, Loc target) {
    return abs(start.c-target.c) + abs(start.r-target.r);
}

int in_sector(int r, int c) {
    return (int)((floor(r/HEIGHT) * 2) + floor(c/WIDTH));
}

double coverage(int sector) {
    double sum = 0.0;
    for (int r = 0; r < HEIGHT; r++) {
        for (int c = 0; c < WIDTH; c++) {
            sum += TREAD[(HEIGHT * floor(sector / 2)) + r][(WIDTH * (sector % 2)) + c] > 0 ? 1 : 0;
            sum += DEAD[(HEIGHT * floor(sector / 2)) + r][(WIDTH * (sector % 2)) + c] > 0 ? 1 : 0;
            sum -= (TREAD[(HEIGHT * floor(sector / 2)) + r][(WIDTH * (sector % 2)) + c] > 0 && DEAD[(HEIGHT * floor(sector / 2)) + r][(WIDTH * (sector % 2)) + c] > 0) ? 1 : 0; 
        }
    }
    return sum / (WIDTH * HEIGHT);
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
            else if (row + NEIGHBORS[i][0] > -1 && row + NEIGHBORS[i][0] < ROWS && col + NEIGHBORS[i][1] > -1 && col + NEIGHBORS[i][1] < COLS) {
                DEAD[row + NEIGHBORS[i][0]][col + NEIGHBORS[i][1]] += 1;
            }
        }
        
        for (int i = 0; i < SECTORS; i++) {
            SECTIONS[i] = coverage(i);
        }
        if (MOVE_TO[id] == -1 && SECTIONS[in_sector(row,col)] == 1) {
            for (int i = 0; i < OPEN_SECTS.size(); i++) {
                if (OPEN_SECTS[i] == in_sector(row,col)) {
                    OPEN_SECTS[i] = OPEN_SECTS[OPEN_SECTS.size() - 1];
                    OPEN_SECTS.pop_back();
                }
            }
            MOVE_TO[id] = OPEN_SECTS.size() == 1 ? OPEN_SECTS[0] : OPEN_SECTS[rand() % (OPEN_SECTS.size()-1)];
        }
        /*if (SECTION[in_sector(row,col)] == 1 || MOVE_TO[id] != -1 || in_sector(row,col) != MOVE_TO[id]) {
            int target_r = FARTHEST[MOVE_TO[id]][0];
            int target_c = FARTHEST[MOVE_TO[id]][1]; 
            int pref_r = target_r < row ? -1 : 1;
            int pref_c = target_c < col ? -1 : 1;
            pref_r = target_r == row ? 0 : pref_r;
            pref_c = target_c == col ? 0 : pref_c;
            
            if (target_r == row && abs(target_c-col) == 1) {
                MOVE_TO[id] = -1;
                return pref_c == -1 ? LEFT : RIGHT; 
            }
            if (target_c == col && abs(target_r-row) == 1) {
                MOVE_TO[id] = -1;
                return pref_r == -1 ? UP : DOWN; 
            }

            if (area.inspect(row + pref_r, col) == DEBRIS) {
                MOVE_TO[id] = -1;
                return pref_r == -1 ? UP : DOWN;
            }
            if (area.inspect(row, col + pref_c) == DEBRIS) {
                MOVE_TO[id] = -1;
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
*/
        int best = -1;
        int bestv = ROWS * COLS;
        for (int i = 0; i < 4; i++) {
            if (row + ADJACENT[i][0] > -1 && row + ADJACENT[i][0] < ROWS && col + ADJACENT[i][1] > -1 && col + ADJACENT[i][1] < COLS) {
                best = TREAD[row + ADJACENT[i][0]][col + ADJACENT[i][1]] < bestv ? i : best;
                bestv = TREAD[row + ADJACENT[i][0]][col + ADJACENT[i][1]] < bestv ? TREAD[row + ADJACENT[i][0]][col + ADJACENT[i][1]] : bestv;
            }
        }

        // if not at a debris field, move randomly:
        switch(best) {
		case 0: return UP;
		case 1: return LEFT;
		case 2: return RIGHT;
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
	if (time % 100 == 0) {
        log << time << " " << endl;
        for (int i = 0; i < LOCATIONS.size(); i++) {
            log << i << "  " << in_sector(LOCATIONS[i].r,LOCATIONS[i].c) << "->" << MOVE_TO[i] << "\t"; 
            if (i % 4 == 3) {
                log << endl;
            }
        }
    }
}


