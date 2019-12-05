
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

const int NEIGHBORS[12][2] = {{-1,0},{0,-1},{0,1},{1,0},{-1,-1},{-1,1},{1,-1},{1,1},{-2,0},{0,-2},{0,2},{2,0}};
const int ADJC[4][2] = {{-1,0},{0,-1},{0,1},{1,0}};

Map map = Map(0,0,MAX_ROBOT_NUM); 

double manhattanDist(Loc start, Loc target) {
    return abs(start.c-target.c) + abs(start.r-target.r);
}

int check_kernel (Area &area, Loc loc) {
    int yeet = 0;
    int row = (loc.r >= map.b_r()) ? (loc.r > map.b_rb()) ? map.b_rb() : loc.r : map.b_r();
    int col = (loc.c >= map.b_c()) ? (loc.c > map.b_cb()) ? map.b_cb() : loc.c : map.b_c();
    for (int i = 0; i < 9; i++) {
        if(map.in_og_range(row + NEIGHBORS[i][0], col + NEIGHBORS[i][1])) {
//            if(area.inspect(row + NEIGHBORS[i][0], col + NEIGHBORS[i][1])== DEBRIS) {
            if(map.peek(row + NEIGHBORS[i][0], col + NEIGHBORS[i][1]).status == TRASH) {
                yeet += 1;
            }
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

	
    log << "Start!" << endl;
}

/* Deciding robot's next move */
Action onRobotAction(int id, Loc loc, Area &area, ostream &log) {
    int row = loc.r; 
	int col = loc.c;
    map.update(loc, ROBOT,id);
   
    for (int i = 0; i < 4; i++) {
        if (map.in_range({row + ADJC[i][0],col + ADJC[i][1]})) {
            if (map.peek({row + ADJC[i][0],col + ADJC[i][1]}).status == DED) {
                Field r = map.peek({row + ADJC[i][0],col + ADJC[i][1]});
                if (ADJC[i][1] != 0) {
                    map.update({row + ADJC[i][0],col + ADJC[i][1]},ROBOT, r.robot);
                    map.fixed(r.robot);
                    return ADJC[i][1] == -1 ? REPAIR_LEFT : REPAIR_RIGHT; 
                }
                if (ADJC[i][0] != 0) {
                    map.update({row + ADJC[i][0],col + ADJC[i][1]},ROBOT,r.robot);
                    map.fixed(r.robot);
                    return ADJC[i][0] == -1 ? REPAIR_UP : REPAIR_DOWN; 
                }
                   
            }
        }
    }

    if (map.locate(id).dead) {
		return COLLECT;
    }
    else if (area.inspect(row, col) == DEBRIS) {
		return COLLECT;
	}
    else if (map.locate(id).fixing != -1) {
        // if it's targeting a broken robot
        Robot r = map.locate(map.locate(id).fixing);
        int target_r = r.loc.r;
        int target_c = r.loc.c;
        int pref_r = target_r < row ? -1 : 1;
        int pref_c = target_c < col ? -1 : 1;
        pref_r = target_r == row ? 0 : pref_r;
        pref_c = target_c == col ? 0 : pref_c;

        // if it's right next to The Broken Robot 
        if (target_r == row && abs(target_c-col) == 1) {
            map.fixed(r.id);
            return pref_c == -1 ? REPAIR_LEFT : REPAIR_RIGHT; 
        }
        if (target_c == col && abs(target_r-row) == 1) {
            map.fixed(r.id);
            return pref_r == -1 ? REPAIR_UP : REPAIR_DOWN; 
        }

        map.update(loc,EMPT);
        
        // chooses the field with debris to move to next
        if (area.inspect(row + pref_r, col) == DEBRIS) {
            return pref_r == -1 ? UP : DOWN;
        }
        if (area.inspect(row, col + pref_c) == DEBRIS) {
            return pref_c == -1 ? LEFT : RIGHT;
        }

        // if no debris and row or col is the same, continue moving in the direction of the broekn robot
        if (pref_r == 0) {
            return pref_c == -1 ? LEFT : RIGHT;
        }
        if (pref_c == 0) {
            return pref_r == -1 ? UP : DOWN;
        }
        
        // choose a random spot
        if (map.in_range({row + pref_r,col})) {
            return pref_r == -1 ? UP : DOWN;
        }
        if (map.in_range({row,col + pref_c})) {
            return pref_c == -1 ? LEFT : RIGHT;
        }
        
        switch(rand() % 1) {
		case 0:
            return pref_r == -1 ? UP : DOWN;
        default:
            return pref_c == -1 ? LEFT : RIGHT;
		}
    }
    else {
        map.update(loc,EMPT);
        // if it's next to a debris field
        
        int check [12] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,};
        vector<int> bestest;
        for (int i = 0; i < 12; i++) {
            if(i < 8 && area.inspect(row + NEIGHBORS[i][0], col + NEIGHBORS[i][1]) == DEBRIS) {
                switch(i) {
                case 0: return UP;
                case 1: return LEFT;
                case 2: return RIGHT;
                case 3: return DOWN;
                case 4: return UP;
                case 5: return UP;
                case 6: return DOWN;
                default: return DOWN;
                }
            }
            if (map.peek(row + NEIGHBORS[i][0], col + NEIGHBORS[i][1]).status == ROBOT) {
                map.treaded({row + NEIGHBORS[i][0], col + NEIGHBORS[i][1]}); 
            }
            check[i] = map.in_range(row + NEIGHBORS[i][0], col + NEIGHBORS[i][1]) ?  map.kernel({row + NEIGHBORS[i][0], col + NEIGHBORS[i][1]}) + ((12 - i) % 4): 0;
            if (check[i] > 1 && i > 8) {
                bestest.push_back(i);
            }
        }

        int k = 4;
        for (int i = 5; i < 12; i++) {
            if (check[i] >= check[k]) {
                k = i;
            }
        } 
        if (k > 0) { 
            switch(bestest[rand() % (bestest.size() - 1)]) {
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
        
        // if it's out of bounds it continues to move until it's no longer out of bounds
        if (row <= map.b_r() && map.in_range({map.b_r() + 1,col})) {
            return DOWN;
        }
        if (row >= map.b_rb() && map.in_range({map.b_rb() - 1,col})) {
            return UP;
        }
        if (col <= map.b_c() && map.in_range({row,map.b_c() + 1})) {
            return RIGHT;
        }
        if (col >= map.b_cb() && map.in_range({row,map.b_cb() - 1})) {
            return LEFT;
        }

       

        // choose the least treaded on field

        int best = -1;
        int bestv = ROWS * COLS;
        for (int i = 0; i < 4; i++) {
            if (map.in_range({row + ADJC[i][0],col + ADJC[i][1]}) && map.peek({row + ADJC[i][0],col + ADJC[i][1]}).status != ROBOT) {
                int robonus = 0;
                for (int i = 0; i < 12; i++) {
                    if (map.in_range({row + ADJC[i][0] + NEIGHBORS[i][0], col + ADJC[i][1] + NEIGHBORS[i][1]})) {
                        if(map.peek(row + ADJC[i][0] + NEIGHBORS[i][0], col + ADJC[i][1] + NEIGHBORS[i][1]).status == ROBOT) {
                            robonus += 1;
                        }
                    }
                }
                best = map.peek({row + ADJC[i][0],col + ADJC[i][1]}).tread + robonus < bestv ? i : best;
                bestv =  map.peek({row + ADJC[i][0],col + ADJC[i][1]}).tread + robonus < bestv ? map.peek({row + ADJC[i][0],col + ADJC[i][1]}).tread + robonus : bestv;
            }
            else if (row+ADJC[i][0] <= map.b_r()-1 && map.peek({row + ADJC[i][0],col + ADJC[i][1]}).status != ROBOT) {
                return DOWN;
            }
            else if (row+ADJC[i][0] >= map.b_rb()+1 && map.peek({row + ADJC[i][0],col + ADJC[i][1]}).status != ROBOT) {
                return UP;
            }
            else if (col+ADJC[i][1] <= map.b_c()-1 && map.peek({row + ADJC[i][0],col + ADJC[i][1]}).status != ROBOT) {
                return RIGHT;
            }
            else if (col+ADJC[i][1] >= map.b_cb()+1 && map.peek({row + ADJC[i][0],col + ADJC[i][1]}).status != ROBOT) {
                return LEFT;
            }
        }

        if (best == -1) {
            return COLLECT;
        }

        //log << bestv << "\t" << map.tread({row + ADJC[best][0],col + ADJC[best][1]}) << endl; 
        
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
    if (map.locate(id).fixer != -1) {
        return;
    }
    map.update(loc,DED,id);
    if (map.locate(id).fixing != -1) {
        onRobotMalfunction(map.locate(id).fixing,map.locate(map.locate(id).fixing).loc, area, log); 
    }
    int min = ROWS * COLS;
    int fix = -1;
    for (int i = 0; i < NUM; i++) {
        if (i != id && map.locate(i).fixing == -1 && !map.locate(i).dead) {
            if (manhattanDist(loc, area.locate(i)) < min) {
                min = manhattanDist(loc, area.locate(i));
                fix = i;
            }
        }
    }
    if (fix == -1) {
        return;
    }
    else {
        map.fixer(id,fix);
	}
    log << "Robot " << fix << " to fix " << id << "\t("<< loc.r << ", " << loc.c << ")" << endl;
}

void onClockTick(int time, ostream &log) {
	if (time % 100 == 0) {
        log << time << "\t" << map.b_r() << ", " << map.b_c() << "\t" << map.b_rb() << ", " << map.b_cb()<< "\t" <<  map.clear() << " / " << map.pile() << "\t" << endl;
    }
    
}


