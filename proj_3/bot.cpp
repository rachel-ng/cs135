
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

const int NEIGHBORS[12][2] = {{-1,0},{0,-1},{0,1},{1,0},{-1,-1},{-1,1},{1,-1},{1,1},{-2,0},{0,-2},{0,2},{2,0}};
const int ADJC[4][2] = {{-1,0},{0,-1},{0,1},{1,0}};

Map map = Map(0,0,MAX_ROBOT_NUM); 

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
            map.update({r,c},area.inspect(r,c) == DEBRIS ? TRASH : EMPT);
            /*if (area.inspect(r,c) != DEBRIS) { 
                map.update({r,c},EMPT);
            }
            if (area.inspect(r,c) == DEBRIS) { 
                map.update({r,c},TRASH);
            }*/
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
    int row = loc.r;  // current row and column
	int col = loc.c;

    map.update(loc, ROBOT,id);

    for (int i = 0; i < 4; i++) {
        if (map.in_range({row + ADJC[i][0],col + ADJC[i][1]})) {
            if (map.peek({row + ADJC[i][0],col + ADJC[i][1]}).status == DED) {
                // fix broken robot if you're next to one
                Field r = map.peek({row + ADJC[i][0],col + ADJC[i][1]});
                map.update({row + ADJC[i][0],col + ADJC[i][1]},ROBOT,r.robot);
                map.fixed(r.robot);
                if (ADJC[i][0] != 0) {
                    // log << "Robot " << id << " fixed " << r.robot << "\t("<< r.loc.r << ", " << r.loc.c << ")" << "\t" << map.ded()<< endl;
                    return ADJC[i][0] == -1 ? REPAIR_UP : REPAIR_DOWN; 
                }
                else if (ADJC[i][1] != 0) {
                    // log << "Robot " << id << " fixed " << r.robot << "\t("<< r.loc.r << ", " << r.loc.c << ")" << "\t" << map.ded()<< endl;
                    return ADJC[i][1] == -1 ? REPAIR_LEFT : REPAIR_RIGHT; 
                }
            }
        }
    }
    
    if (map.locate(id).dead) {
        // dead robots don't move
		if (map.locate(id).fixer == -1) {
            map.fix(loc,id);
        }
        return COLLECT;
    }
    else if (area.inspect(row, col) == DEBRIS) {
        // on debris field
		return COLLECT;
	}
    else if (map.locate(id).fixing != -1) {
        // targeting a broken robot
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
            // log << "Robot " << id << " fixed " << r.id << "\t("<< r.loc.r << ", " << r.loc.c << ")" << "\t" << map.ded()<< endl;
            return pref_c == -1 ? REPAIR_LEFT : REPAIR_RIGHT; 
        }
        if (target_c == col && abs(target_r-row) == 1) {
            map.fixed(r.id);
            // log << "Robot " << id << " fixed " << r.id << "\t("<< r.loc.r << ", " << r.loc.c << ")" << "\t" << map.ded()<< endl;
            return pref_r == -1 ? REPAIR_UP : REPAIR_DOWN; 
        }

        map.update(loc,EMPT);
        
        // if row or col is the same, continue moving in the direction of the broken robot
        if (pref_r == 0 && map.peek(row + pref_r, col + pref_c).status != ROBOT) {
            return pref_c == -1 ? LEFT : RIGHT;
        }
        else if (pref_r == 0) {
            return map.in_range(row-1, col) ? UP : DOWN; 
        }
        if (pref_c == 0 && map.peek(row + pref_r, col + pref_c).status != ROBOT) {
            return pref_r == -1 ? UP : DOWN;
        }
        else if (pref_c == 0) {
            return map.in_range(row, col-1) ? LEFT : RIGHT;
        }

        // chooses the field with debris to move to next
        if (map.peek(row + pref_r, col).status == TRASH) {
            return pref_r == -1 ? UP : DOWN;
        }
        if (map.peek(row, col + pref_c).status == TRASH) {
            return pref_c == -1 ? LEFT : RIGHT;
        }
                
        // choose a random spot
        if (map.in_range({row + pref_r,col}) && map.peek(row + pref_r, col).status != ROBOT) {
            return pref_r == -1 ? UP : DOWN;
        }
        if (map.in_range({row,col + pref_c}) && map.peek(row, col + pref_c).status != ROBOT) {
            return pref_c == -1 ? LEFT : RIGHT;
        }
        
        switch(rand() % 1) {
		case 0: return pref_r == -1 ? UP : DOWN;
        default: return pref_c == -1 ? LEFT : RIGHT;
		}
    }
    else {

        map.update(loc,EMPT);
        
        //int check [12] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,};

        // if it's next to a debris field
        for (int i = 0; i < 12; i++) {
            if(map.peek(row + NEIGHBORS[i][0], col + NEIGHBORS[i][1]).status == TRASH) {
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
            if (!map.bots({row + NEIGHBORS[i][0], col + NEIGHBORS[i][1]})) {
                map.treaded({row + NEIGHBORS[i][0], col + NEIGHBORS[i][1]}); 
            }
            //check[i] = map.in_range(row + NEIGHBORS[i][0], col + NEIGHBORS[i][1]) ?  map.kernel({row + NEIGHBORS[i][0], col + NEIGHBORS[i][1]}) + ((12 - i) % 4): 0;
        }

        /*int k = 4;
        for (int i = 5; i < 12; i++) {
            if (check[i] >= check[k]) {
                k = i;
            }
        } */
        
        // if it's out of bounds it continues to move until it's no longer out of bounds
        if (row <= map.b_r() && map.in_range({map.b_r() + 1,col}) && map.bots({row+1,col})) {
            return DOWN;
        }
        /*else if (col <= map.b_c() && map.in_range({row,map.b_c() + 1}) && map.bots({row,col+1})) {
            return RIGHT;
        }
        else if (col >= map.b_cb() && map.in_range({row,map.b_cb() - 1}) && map.bots({row,col-1})) {
            return LEFT;
        }*/
 
        if (row >= map.b_rb() && map.in_range({map.b_rb() - 1,col}) && map.bots({row-1,col})) {
            return UP;
        }
        /*else if (col <= map.b_c() && map.in_range({row,map.b_c() + 1}) && map.bots({row,col+1})) {
            return RIGHT;
        }
        else if (col >= map.b_cb() && map.in_range({row,map.b_cb() - 1}) && map.bots({row,col-1})) {
            return LEFT;
        }*/
        
        if (col <= map.b_c() && map.in_range({row,map.b_c() + 1}) && map.bots({row,col+1})) {
            return RIGHT;
        }
        /*else if (row <= map.b_r() && map.in_range({map.b_r() + 1,col}) && map.bots({row+1,col})) {
            return DOWN;
        }
        else if (row >= map.b_rb() && map.in_range({map.b_rb() - 1,col}) && map.bots({row-1,col})) {
            return UP;
        }*/
        
        if (col >= map.b_cb() && map.in_range({row,map.b_cb() - 1}) && map.bots({row,col-1})) {
            return LEFT;
        }
        /*else if (row <= map.b_r() && map.in_range({map.b_r() + 1,col}) && map.bots({row+1,col})) {
            return DOWN;
        }
        else if (row >= map.b_rb() && map.in_range({map.b_rb() - 1,col}) && map.bots({row-1,col})) {
            return UP;
        }*/

       

        // choose the least treaded on field
        int best = -1;
        int bestv = ROWS * COLS;
        for (int i = 0; i < 4; i++) {
            if (map.in_range({row + ADJC[i][0],col + ADJC[i][1]}) && map.peek({row + ADJC[i][0],col + ADJC[i][1]}).status != ROBOT) {
                // bonus for previous locations + nearby robots 
                int robonus = comploc(map.peek(row + ADJC[i][0],col + ADJC[i][1]).loc, map.locate(id).ploc) ? (NUM/2) : 0;
                for (int i = 0; i < 12; i++) {
                    if (map.in_range({row + ADJC[i][0] + NEIGHBORS[i][0], col + ADJC[i][1] + NEIGHBORS[i][1]})) {
                        robonus += map.peek(row + ADJC[i][0] + NEIGHBORS[i][0], col + ADJC[i][1] + NEIGHBORS[i][1]).status == ROBOT ? (NUM / 2) : 0;
                    }
                }
                
                best = map.peek({row + ADJC[i][0],col + ADJC[i][1]}).tread + robonus < bestv ? i : best;
                bestv =  map.peek({row + ADJC[i][0],col + ADJC[i][1]}).tread + robonus < bestv ? map.peek({row + ADJC[i][0],col + ADJC[i][1]}).tread + robonus : bestv;
            
            }
            else if (row+ADJC[i][0] <= map.b_r()-1 && map.bots({row + ADJC[i][0],col + ADJC[i][1]})) {
                return DOWN;
            }
            else if (row+ADJC[i][0] >= map.b_rb()+1 && map.bots({row + ADJC[i][0],col + ADJC[i][1]})) {
                return UP;
            }
            else if (col+ADJC[i][1] <= map.b_c()-1 && map.bots({row + ADJC[i][0],col + ADJC[i][1]})) {
                return RIGHT;
            }
            else if (col+ADJC[i][1] >= map.b_cb()+1 && map.bots({row + ADJC[i][0],col + ADJC[i][1]})) {
                return LEFT;
            }
        }

        // if there's no place to go just stay there 
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
    // map fix function
    map.fix(loc,id);
    log << "Robot " << map.locate(id).fixer << " to fix " << id << "\t("<< loc.r << ", " << loc.c << ")" << "\t" << map.ded()<< endl;
}

void onClockTick(int time, ostream &log) {
	if (time % 100 == 0) {
        log << time << "\t" << map.b_r() << ", " << map.b_c() << "\t" << map.b_rb() << ", " << map.b_cb()<< "\t" <<  map.clear() << " / " << map.pile() << endl;
    }
    
}


