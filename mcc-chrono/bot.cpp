
/*
Author: Rachel Ng 
Course: CSCI-135
Instructor: Maryash
Assignment: Project 3

the boi
*/

#include <cstdlib>
#include <iostream>
#include <vector> 
#include <cmath>
#include "bot.h"

#define DEBUG
#ifdef DEBUG
#define ERR(x) std::cerr << x;
#else
#define ERR(x)
#endif

using namespace std;

enum Places {EMPT, TRASH, UNDEF, ROBOT, DED};

struct Field {
    Places status;
    Loc loc;
    bool covered;
    bool claimed;
    int tread;
    int dead;
    int robot;
    int intended;
};

class Robot {
public:
    Loc loc = {-1,-1};
    Loc ploc = {-1,-1}; // previous location 
    Loc target = {-1,-1};
    bool dead = false;
    int id;
    int fixer = -1; // robot that will fix this
    int fixing = -1; // will fix this robot
    
    Robot(int);
    void update(Loc l);
    void update(Loc l, bool d);
    int fixers(); 
    int fixings();
};

class Map {
    std::vector<std::vector <Field> > fields;
    std::vector<Robot> robots; 
    std::vector<int> dead; 
    int ROWS;
    int COLS;
    int NUM;
    int NUMRT;
    int RSIZE;
    int CSIZE;
    int KSIZE;
    int BOUND_R = 0;
    int BOUND_C = 0;
    int BOUND_RB;
    int BOUND_CB;
    int cleared = 0;
    int def_clear = 0;
    int piles; 
    int broken = 0;

public:
    std::vector<int> rip ();
    Map (int row, int col, int num);
    bool in_og_range (Loc loc);
    bool in_og_range (int r, int c);
    bool in_range (Loc loc);
    bool in_range (int r, int c);
    Robot locate (int id);
    Robot* robot (int id);
    Field peek (int row, int col);
    Field peek (Loc loc);
    int check_u (Loc loc);
    int check_d (Loc loc);
    int check_l (Loc loc);
    int check_r (Loc loc);
    int check_u (Loc loc, int rows, int cols);
    int check_d (Loc loc, int rows, int cols);
    int check_l (Loc loc, int rows, int cols);
    int check_r (Loc loc, int rows, int cols);
    int kernel (Loc loc);
    int kernel (Loc loc, int size);
    int kernelr (Loc loc);
    int kernelr (Loc loc, int size);
    int kernelc (Loc loc);
    int kernelc (Loc loc, int size);
    bool update (Loc loc, Places p);
    bool update (Loc loc, Places p, int id);
    void treaded (Loc loc);
    void treaded (Loc loc, int diff);
    void deaded (Loc loc);
    void set_default();
    void fix ();
    void fix (Loc loc, int id);
    void fix (Loc loc, int id, bool force);
    void fixer (int id, int fix);
    void fixed (int id);
    void nearest (int id);
    void nearest (int id, Loc loc);
    void claim (int id, Loc loc);
    void unclaim (int id);
    void unclaim (Loc loc);
    bool bots(Loc loc);
    bool bots(int row, int col);
    bool rbots(Loc loc);
    bool rbots(int row, int col);
    bool dedbots(Loc loc);
    bool dedbots(int row, int col);
    int clear ();
    int pile ();
    int ded ();
    void bound();
    void bound_r();
    void bound_c();
    void bound_rb();
    void bound_cb();
    int b_r();
    int b_c();
    int b_rb();
    int b_cb();
};


double manhattanDist(Loc start, Loc target) { // manhattan distance 
    return abs(start.c-target.c) + abs(start.r-target.r);
}

bool comploc (Loc a, Loc b) { // compare locations 
    return (a.r == b.r && a.c == b.c);
}

Robot::Robot (int i) { // set up robots 
    id = i;
}

void Robot::update (Loc l) { 
    ploc = loc;
    loc = l;
}

void Robot::update (Loc l, bool d) {
    ploc = loc;
    loc = l;
    dead = d;
}

int Robot::fixers () {
    return fixer;
}

int Robot::fixings () {
    return fixing;
}

std::vector<int> Map::rip () {
    return dead;
}

Map::Map (int row, int col, int num) {
    ROWS = row;
    COLS = col;
    NUM = num;
    NUMRT = sqrt(NUM);
    BOUND_CB  = COLS;
    BOUND_RB = ROWS;
    piles = ROWS * COLS;
    fields.resize(ROWS, std::vector<Field>(COLS, {UNDEF,{-1,-1},false, false,0,0,-1,-1}));
    robots.resize(NUM,Robot(-1));
    for (int i = 0; i < NUM; i++) {
        robots[i] = Robot(i);
    }
    RSIZE = ROWS / NUMRT;
    CSIZE = COLS / NUMRT;
    KSIZE = RSIZE > CSIZE ? RSIZE : CSIZE;
}

bool Map::in_og_range (Loc loc) {
    return (loc.r >= 0 && loc.c >= 0 && loc.r < ROWS && loc.c < COLS);
}

bool Map::in_og_range (int r, int c) {
    return (r >= 0 && c >= 0 && r < ROWS && c < COLS);
}

bool Map::in_range (Loc loc) {
    return (loc.r >= BOUND_R && loc.c >= BOUND_C && loc.r < BOUND_RB && loc.c < BOUND_CB);
}

bool Map::in_range (int r, int c) {
    return (r >= BOUND_R && c >= BOUND_C && r < BOUND_RB && c < BOUND_CB);
}

Robot Map::locate (int id) {
    return robots[id];
}

Robot* Map::robot (int id) {
    return &robots[id];
}

Field Map::peek (int row, int col) {
    Loc loc = {row,col};
    if (in_og_range(loc)) {
        return fields[row][col];
    }
    return {UNDEF, {-1,-1},  false, false, -1, -1, -1, -1};
}

Field Map::peek (Loc loc) {
    if (in_og_range(loc)) {
        return fields[loc.r][loc.c];
    }
    return {UNDEF, {-1,-1}, false, false, -1, -1, -1, -1};
}   

int Map::check_u (Loc loc) {
    int yeet = 0;
    for (int r = -1; r >= -2; r--) {
        for (int c = -2; c <= 2; c++) {
            if(in_og_range(loc.r + r, loc.c + c)) {
                if (bots(loc.r + r, loc.c + c)) {
                    yeet += 1;
                }
            }
        }
    }
    return yeet;
}

int Map::check_u (Loc loc, int rows, int cols) {
    int yeet = 0;
    for (int r = -1; r >= -rows; r--) {
        for (int c = -cols; c <= cols; c++) {
            if(in_og_range(loc.r + r, loc.c + c)) {
                if (bots(loc.r + r, loc.c + c)) {
                    yeet += 1;
                }
            }
        }
    }
    return yeet;
}

int Map::check_d (Loc loc) {
    int yeet = 0;
    for (int r = 1; r <= 2; r++) {
        for (int c = -2; c <= 2; c++) {
            if(in_og_range(loc.r + r, loc.c + c)) {
                if (bots(loc.r + r, loc.c + c)) {
                    yeet += 1;
                }
            }
        }
    }
    return yeet;
}

int Map::check_d (Loc loc, int rows, int cols) {
    int yeet = 0;
    for (int r = 0; r <= rows; r++) {
        for (int c = -cols; c <= cols; c++) {
            if(in_og_range(loc.r + r, loc.c + c)) {
                if (bots(loc.r + r, loc.c + c)) {
                    yeet += 1;
                }
            }
        }
    }
    return yeet;
}

int Map::check_r (Loc loc) {
    int yeet = 0;
    for (int r = -2; r <= 2; r++) {
        for (int c = 0; c <= 2; c++) {
            if(in_og_range(loc.r + r, loc.c + c)) {
                if (bots(loc.r + r, loc.c + c)) {
                    yeet += 1;
                }
            }
        }
    }
    return yeet;
}

int Map::check_r (Loc loc, int rows, int cols) {
    int yeet = 0;
    for (int r = -rows; r <= rows; r++) {
        for (int c = 0; c <= cols; c++) {
            if(in_og_range(loc.r + r, loc.c + c)) {
                if (bots(loc.r + r, loc.c + c)) {
                    yeet += 1;
                }
            }
        }
    }
    return yeet;
}

int Map::check_l (Loc loc) {
    int yeet = 0;
    for (int r = -2; r <= 2; r++) {
        for (int c = 0; c >= -2; c--) {
            if(in_og_range(loc.r + r, loc.c + c)) {
                if (bots(loc.r + r, loc.c + c)) {
                    yeet += 1;
                }
            }
        }
    }
    return yeet;
}

int Map::check_l (Loc loc, int rows, int cols) {
    int yeet = 0;
    for (int r = -rows; r <= rows; r++) {
        for (int c = 0; c >= -cols; c--) {
            if(in_og_range(loc.r + r, loc.c + c)) {
                if (bots(loc.r + r, loc.c + c)) {
                    yeet += 1;
                }
            }
        }
    }
    return yeet;
}

int Map::kernel (Loc loc) { // checks debris of specified kernel 
    int yeet = 0;
    //int row = (loc.r >= BOUND_R) ? (loc.r > map.b_rb()) ? map.b_rb() : loc.r : map.b_r();
    int row = (loc.r >= BOUND_R) ? (loc.r > BOUND_RB) ? BOUND_RB : loc.r : BOUND_R;
    int col = (loc.c >= BOUND_C) ? (loc.c > BOUND_CB) ? BOUND_CB : loc.c : BOUND_C;

    for (int r = -3; r <= 3; r++) {
        for (int c = -3; c <= 3; c++) {
            if(in_og_range(row + r, col + c)) {
                if (peek(row + r, col + c).status == TRASH) {
                    yeet += 1;
                }
            }
        }
    }
    return yeet;
}

int Map::kernel (Loc loc, int size) {  // checks debris of specified kernel
    int yeet = 0;
    //int row = (loc.r >= BOUND_R) ? (loc.r > map.b_rb()) ? map.b_rb() : loc.r : map.b_r();
    int row = (loc.r >= BOUND_R) ? (loc.r > BOUND_RB) ? BOUND_RB : loc.r : BOUND_R;
    int col = (loc.c >= BOUND_C) ? (loc.c > BOUND_CB) ? BOUND_CB : loc.c : BOUND_C;

    for (int r = -size; r <= size; r++) {
        for (int c = -size; c <= size; c++) {
            if(in_og_range(row + r, col + c) && !comploc(loc,{row + r, col + c})) {
                if (peek(row + r, col + c).status == TRASH) {
                    yeet += 1;
                }
            }
        }
    }
    return yeet;
}

int Map::kernelr (Loc loc) {  // checks robots of specified kernel
    int yeet = 0;
    //int row = (loc.r >= BOUND_R) ? (loc.r > map.b_rb()) ? map.b_rb() : loc.r : map.b_r();
    int row = (loc.r >= BOUND_R) ? (loc.r > BOUND_RB) ? BOUND_RB : loc.r : BOUND_R;
    int col = (loc.c >= BOUND_C) ? (loc.c > BOUND_CB) ? BOUND_CB : loc.c : BOUND_C;

    for (int r = -3; r <= 3; r++) {
        for (int c = -3; c <= 3; c++) {
            if(in_og_range(row + r, col + c) && !comploc(loc,{row + r, col + c})) {
                if (peek(row + r, col + c).status == ROBOT) {
                    yeet += 1;
                }
            }
        }
    }
    return yeet;
}

int Map::kernelr (Loc loc, int size) {  // checks robots of specified kernel
    int yeet = 0;
    //int row = (loc.r >= BOUND_R) ? (loc.r > map.b_rb()) ? map.b_rb() : loc.r : map.b_r();
    int row = (loc.r >= BOUND_R) ? (loc.r > BOUND_RB) ? BOUND_RB : loc.r : BOUND_R;
    int col = (loc.c >= BOUND_C) ? (loc.c > BOUND_CB) ? BOUND_CB : loc.c : BOUND_C;

    for (int r = -size; r <= size; r++) {
        for (int c = -size; c <= size; c++) {
            if(in_og_range(row + r, col + c) && !comploc(loc,{row + r, col + c})) {
                if (peek(row + r, col + c).status == ROBOT) {
                    yeet += 1;
                }
            }
        }
    }
    return yeet;
}

int Map::kernelc (Loc loc) {  // checks robots of specified kernel
    int yeet = 0;
    //int row = (loc.r >= BOUND_R) ? (loc.r > map.b_rb()) ? map.b_rb() : loc.r : map.b_r();
    int row = (loc.r >= BOUND_R) ? (loc.r > BOUND_RB) ? BOUND_RB : loc.r : BOUND_R;
    int col = (loc.c >= BOUND_C) ? (loc.c > BOUND_CB) ? BOUND_CB : loc.c : BOUND_C;

    for (int r = -3; r <= 3; r++) {
        for (int c = -3; c <= 3; c++) {
            if(in_og_range(row + r, col + c) && !comploc(loc,{row + r, col + c})) {
                if (peek(row + r, col + c).claimed) {
                    yeet += 1;
                }
            }
        }
    }
    return yeet;
}

int Map::kernelc (Loc loc, int size) {  // checks robots of specified kernel
    int yeet = 0;
    //int row = (loc.r >= BOUND_R) ? (loc.r > map.b_rb()) ? map.b_rb() : loc.r : map.b_r();
    int row = (loc.r >= BOUND_R) ? (loc.r > BOUND_RB) ? BOUND_RB : loc.r : BOUND_R;
    int col = (loc.c >= BOUND_C) ? (loc.c > BOUND_CB) ? BOUND_CB : loc.c : BOUND_C;

    for (int r = -size; r <= size; r++) {
        for (int c = -size; c <= size; c++) {
            if(in_og_range(row + r, col + c) && !comploc(loc,{row + r, col + c})) {
                if (peek(row + r, col + c).claimed) {
                    yeet += 1;
                }
            }
        }
    }
    return yeet;
}
bool Map::update (Loc loc, Places p) {
    if (in_og_range(loc)) {
        Places prev = fields[loc.r][loc.c].status;
        if (fields[loc.r][loc.c].loc.r == -1 && fields[loc.r][loc.c].loc.c == -1) {
            fields[loc.r][loc.c].loc = loc;
        }
        fields[loc.r][loc.c].status = p;
        fields[loc.r][loc.c].robot = -1;
        if (p == TRASH) {
            cleared += 1;
            fields[loc.r][loc.c].tread -= 1;
            for (int r = -2; r < 2; r++) {
                for (int c = -2; c < 2; c++) {
                    if(in_og_range({loc.r + r,loc.c + c})) {
                        fields[loc.r + r][loc.c + c].tread -= 1;
                    }
                }
            }
        }
        if (prev == TRASH) {
            cleared -= 1;
            fields[loc.r][loc.c].tread = 0;
            fields[loc.r][loc.c].dead = 1;
        }
        if (p == EMPT) {
            fields[loc.r][loc.c].covered = true;
            fields[loc.r][loc.c].tread += 1;
            fields[loc.r][loc.c].dead += 1;
            unclaim(loc);
        }
        
        if (p!= TRASH && (loc.r <= BOUND_R || loc.c <= BOUND_C || loc.r > BOUND_RB || loc.c > BOUND_CB)) { 
            fields[loc.r][loc.c].tread += 1;
            return true;
        }
        
        // do bounding 
        if(loc.r > BOUND_R || loc.r <= BOUND_RB) {
            bound_r(); 
            bound_rb(); 
        }
        if(loc.c > BOUND_C || loc.c <= BOUND_CB) {
            bound_c();
            bound_cb();
        }
        
        return true;
    }
    return false;
}

bool Map::update (Loc loc, Places p, int id) {
    if (in_og_range(loc)) {
        Places prev = fields[loc.r][loc.c].status;
        if (fields[loc.r][loc.c].loc.r == -1 && fields[loc.r][loc.c].loc.c == -1) {
            fields[loc.r][loc.c].loc = loc;
        }
        fields[loc.r][loc.c].status = p;
        fields[loc.r][loc.c].robot = -1;
        if (p == TRASH) {
            cleared += 1;
            fields[loc.r][loc.c].tread -= 1;
            for (int r = -2; r < 2; r++) {
                for (int c = -2; c < 2; c++) {
                    if(in_og_range({loc.r + r,loc.c + c})) {
                        fields[loc.r + r][loc.c + c].tread -= 1;
                    }
                }
            }
        }
        if (prev == TRASH) { 
            cleared -= 1;
            fields[loc.r][loc.c].tread = 0;
            fields[loc.r][loc.c].dead = 1;
        }
        if (p == EMPT) {
            fields[loc.r][loc.c].covered = true;
            fields[loc.r][loc.c].tread += 1;
            fields[loc.r][loc.c].dead += 1;
            unclaim(loc);
        }
        else if (p == ROBOT) { // update robot locations 
            robots[id].update(loc);
            fields[loc.r][loc.c].tread += 2;
            fields[loc.r][loc.c].dead += 1;
            fields[loc.r][loc.c].robot = id;
        }
        else if (p == DED) { // update dead robots 
            robots[id].update(loc, true);
            fields[loc.r][loc.c].robot= id;
            bool s = false;
            
            for (int i = 0; i < dead.size(); i++) {
                s = dead[i] == id ? true : false;
            }
            if (!s) {
                dead.push_back(id); 
            }
        }

        if (p!= TRASH && (loc.r <= BOUND_R || loc.c <= BOUND_C || loc.r > BOUND_RB || loc.c > BOUND_CB)) { 
            fields[loc.r][loc.c].tread += 1;
            return true;
        }

        // do bounding 
        if(loc.r > BOUND_R || loc.r <= BOUND_RB) {
            bound_r(); 
            bound_rb(); 
        }
        if(loc.c > BOUND_C || loc.c <= BOUND_CB) {
            bound_c();
            bound_cb();
        }
        
        return true;
    }
    return false;
}

void Map::fix () { // check for robots that need fixing 
    for (int i = 0; i < dead.size(); i++) {
        if (robots[dead[i]].fixer == -1) {
            fix(robots[dead[i]].loc, dead[i]);
            return;
        }
    }
}

void Map::fix (Loc loc, int id) { // fix a robot 
    if (robots[id].fixer != -1) {
        return;
    }
    if (!comploc(robots[id].target,{-1,-1})) {
        fields[robots[id].target.r][robots[id].target.c].claimed = false;
        robots[id].target = {-1,-1};
    }
    // change status to dead
    update(loc,DED,id);
    if (robots[id].fixing != -1) { // assigns new fixer to the robot this was supposed to be fixing (if available)
        fix(robots[id].loc, robots[id].fixing);
    }
    // find closest robot and assign to fix this one 
    int min = ROWS * COLS;
    int f = -1;
    for (int i = 0; i < NUM; i++) {
        if (i != id && robots[i].fixing == -1 && !robots[i].dead) {
            if (manhattanDist(loc, robots[i].loc) < min) {
                min = manhattanDist(loc, robots[i].loc);
                f = i;
            }
        }
    }
    if (f == -1) { // if no fixers available 
        return;
    }
    else {
        fixer(id,f);
	}
} 

void Map::fix (Loc loc, int id, bool force) { // fix a robot 
    if (robots[id].fixer != -1 && !force) {
        return;
    }
    if (robots[id].fixer != -1 && force) {
        robots[robots[id].fixer].fixing = -1; 
    }
    if (!comploc(robots[id].target,{-1,-1})) {
        fields[robots[id].target.r][robots[id].target.c].claimed = false;
        robots[id].target = {-1,-1};
    }
    // change status to dead
    update(loc,DED,id);
    if (robots[id].fixing != -1) { // assigns new fixer to the robot this was supposed to be fixing (if available)
        fix(robots[id].loc, robots[id].fixing);
    }
    // find closest robot and assign to fix this one 
    int min = ROWS * COLS;
    int f = -1;
    for (int i = 0; i < NUM; i++) {
        if (i != id && robots[i].fixing == -1 && !robots[i].dead) {
            if (manhattanDist(loc, robots[i].loc) < min) {
                min = manhattanDist(loc, robots[i].loc);
                f = i;
            }
        }
    }
    fixer(id,f);
} 

void Map::fixer (int id, int fix) { // assign a fixer 
    robots[id].fixer = fix;
    robots[fix].fixing = id;
    robots[id].target = {-1,-1};
    robots[fix].target = {-1,-1};
    broken += 1;
}

void Map::fixed (int id) { // upon fixing a robot  
    int f = robots[id].fixer;
    robots[f].fixing = -1;
    robots[id].fixer = -1;
    robots[id].dead = false;
    broken -= 1;
    if (dead.size() > 1) { // takes the robot out of the fix list 
        for (int i = 0; i < dead.size(); i++) {
            if (dead[i] == id) {
                dead[i] = dead[dead.size()-1];
                dead.pop_back();
            }
        }
    }
    else {
        dead.pop_back();
    }
    fix(); // check if there are any robots that still need to be fixed 
}

void Map::nearest (int id) {
    Loc loc = robots[id].loc;
    Loc best = {BOUND_R, BOUND_C};
    int bestd = ROWS * COLS;
    int bestk = -1000;
    for (int r = BOUND_R; r < BOUND_RB; r++) {
        for (int c = BOUND_C; c < BOUND_CB; c++) {
    /*        if (in_range(r,c)) {
                Loc l = {r,c};
                int a = (manhattanDist(l,{r,BOUND_C}) - manhattanDist(loc,l));
                int b = (manhattanDist(l,{r,BOUND_CB}) - manhattanDist(loc,l));
                int e = (manhattanDist(l,{BOUND_R,c}) - manhattanDist(loc,l));
                int d = (manhattanDist(l,{BOUND_RB,c}) - manhattanDist(loc,l));
                int a = manhattanDist(loc,l) - manhattanDist(l,{r,BOUND_C});
                int b = manhattanDist(loc,l) - manhattanDist(l,{r,BOUND_CB});
                int e = manhattanDist(loc,l) - manhattanDist(l,{BOUND_R,c});
                int d = manhattanDist(loc,l) - manhattanDist(l,{BOUND_RB,c});
                int boosted = (a > b) ? ((b > e) ? ((e > d) ? d : e) : ((b > d) ? d : b)) : ((a > e) ? ((e > d) ? d : e) : ((a > d) ? d : a));
                best = !rbots(loc) && !comploc(loc,l) && bestd > manhattanDist(loc,l) && bestk < kernel(l) - kernelr(l) && kernel(l) > 0 ? l : best;
                bestdl = !rbots(loc) && !comploc(loc,l) && bestd > manhattanDist(loc,l) && kernel(l) > 0 ? l : bestdl;
                bestkl = !rbots(loc) && !comploc(loc,l) && bestk < kernel(l) - kernelr(l) && kernel(l) > 0 ? l : bestkl;
      */
            if (comploc(loc, {r, c}) || peek(r,c).status != TRASH || peek(r,c).covered || peek(r,c).claimed || rbots({r,c})) {
                continue;
            }
            if (manhattanDist(loc, {r, c}) < bestd || bestk < kernel({r,c}) - kernelr({r,c},6)) {
                bestd = manhattanDist(loc, {r, c});
                bestk = kernel({r,c}) - kernelr({r,c});
                best = {r, c};
            }
        }
    }

    if (!comploc(loc, best)) {
        fields[best.r][best.c].claimed = true;
        fields[loc.r][loc.c].intended = id;
        robots[id].target = best;
        ERR(robots[id].target.r << ", " << robots[id].target.c << endl);
    }
}

void Map::nearest (int id, Loc loc) {
    ERR(loc.r << ", " << loc.c << " -> ");
    fields[loc.r][loc.c].claimed = true;
    fields[loc.r][loc.c].intended = id;
    robots[id].target = loc;
    ERR(robots[id].target.r << ", " << robots[id].target.c << endl);
}


void Map::claim (int id, Loc loc) {
    fields[loc.r][loc.c].claimed = true;
    fields[loc.r][loc.c].intended = id;
}

void Map::unclaim (int id) {
    fields[robots[id].target.r][robots[id].target.c].claimed = false;
    fields[robots[id].target.r][robots[id].target.c].intended = -1;
    robots[id].target = {-1,-1};
}

void Map::unclaim (Loc loc) {
    fields[loc.r][loc.c].claimed = false;
    if (fields[loc.r][loc.c].intended != -1) {
        robots[fields[loc.r][loc.c].intended].target = {-1,-1};
    }
    fields[loc.r][loc.c].intended = -1;
}

bool Map::bots(Loc loc) { // if alive or dead robots 
    return (peek(loc).status == ROBOT || peek(loc).status == DED);
}

bool Map::bots(int row, int col) { // if alive or dead robots 
    return in_og_range(row,col) ? (peek(row,col).status == ROBOT || peek(row,col).status == DED) : false;
}

bool Map::rbots(Loc loc) { // if alive robots 
    return peek(loc).status == ROBOT;
}

bool Map::rbots(int row, int col) { // if alive robots 
    return in_og_range(row,col) ? peek(row,col).status == ROBOT : false;
}

bool Map::dedbots(Loc loc) { // if dead robots 
    return peek(loc).status == DED;
}

bool Map::dedbots(int row, int col) { // if dead robots 
    return in_og_range(row,col) ? peek(row,col).status == DED : false;
}

int Map::clear () {
    return cleared;
}

int Map::pile () {
    return piles;
}

int Map::ded () {
    return dead.size();
}

void Map::treaded (Loc loc) {
    fields[loc.r][loc.c].tread += 1;
}

void Map::treaded (Loc loc, int diff) {
    fields[loc.r][loc.c].tread += diff;
}

void Map::deaded (Loc loc) {
    fields[loc.r][loc.c].dead += 1;
}

// fixes upper bounds 
void Map::bound_r() {
    bool rip = true;
    for (int i = BOUND_R; i < BOUND_RB; i++) {
        for (int c = BOUND_C; c < BOUND_CB; c++) {
            if (!fields[i][c].covered) {
                rip = false;
                break;
            }
        }
        //if (rip && BOUND_RB-BOUND_R > NUMRT) { // adjust bound 
        if (rip) { // adjust bound 
            BOUND_R = i;
        }
        else {
            break;
        }
    }
}

// fixes left bounds 
void Map::bound_c() {
    bool rip = true;
    for (int i = BOUND_C; i < BOUND_CB; i++) {
        for (int r = BOUND_R; r < BOUND_RB; r++) {
            if (!fields[r][i].covered) {
                rip = false;
                break;
            }
        }
        //if (rip && BOUND_CB-BOUND_C > NUMRT) { // adjust bound 
        if (rip) { // adjust bound 
            BOUND_C = i;
        }
        else {
            break;
        }
    }
}

// fixes lower bounds 
void Map::bound_rb() {
    for (int i = BOUND_RB-1; i >= BOUND_R; i--) {
        bool rip = true;
        for (int c = BOUND_C; c < BOUND_CB; c++) {
            if (!fields[i][c].covered) {
                rip = false;
                break;
            }
        }
        //if (rip && BOUND_RB-BOUND_R > NUMRT) { // adjust bound 
        if (rip) { // adjust bound 
            BOUND_RB = i;
        }
        else {
            break;
        }
    }
}

// fixes right bounds 
void Map::bound_cb() {
    for (int i = BOUND_CB-1; i >= BOUND_C; i--) {
        bool rip = true;
        for (int r = BOUND_R; r < BOUND_RB; r++) {
            if (!fields[r][i].covered) {
                rip = false;
                break;
            }
        }
        //if (rip && BOUND_CB-BOUND_C > NUMRT) { // adjust bound 
        if (rip) { // adjust bound 
            BOUND_CB = i;
        }
        else {
            break;
        }
    }
}

int Map::b_r() { // upper bound 
    return BOUND_R;
}

int Map::b_c() { // left bound 
    return BOUND_C;
}

int Map::b_rb() { // lower bound 
    return BOUND_RB;
}

int Map::b_cb() { // right bound 
    return BOUND_CB;
}
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
    
    // set up map 
    map = Map(ROWS,COLS,NUM);
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            map.update({r,c},area.inspect(r,c) == DEBRIS ? TRASH : EMPT);
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

    if (!map.robot(id)->dead) {
        map.update(loc, ROBOT,id);
    }

    if(map.robot(id)->fixing == -1 && !map.robot(id)->dead) {
        for (int i = 0; i < 4; i++) {
            if (map.dedbots({row + ADJC[i][0],col + ADJC[i][1]})) {
                map.fix({row + ADJC[i][0],col + ADJC[i][1]},map.peek({row + ADJC[i][0],col + ADJC[i][1]}).robot, true);
            }
        }
    }
   
    if (map.robot(id)->dead) {
        // dead robots don't move
		if (map.robot(id)->fixer == -1) {
            map.fix(loc,id);
        }
        return COLLECT;
    }
    else if (area.inspect(row, col) == DEBRIS) {
        // on debris field
		return COLLECT;
	}
    else if (map.robot(id)->fixing != -1) {
        fix:
        // targeting a broken robot
        Robot *r = map.robot(map.robot(id)->fixing);
        int target_r = r->loc.r;
        int target_c = r->loc.c;
        // preferred directions
        int pref_r = target_r < row ? -1 : 1;
        int pref_c = target_c < col ? -1 : 1;
        pref_r = target_r == row ? 0 : pref_r;
        pref_c = target_c == col ? 0 : pref_c;

        // if it's right next to The Broken Robot 
        if (target_r == row && abs(target_c - col) == 1) {
            map.fixed(r->id);
            // log << "Robot " << id << " fixed " << r.id << "\t("<< r.loc.r << ", " << r.loc.c << ")" << "\t" << map.ded()<< endl;
            return pref_c == -1 ? REPAIR_LEFT : REPAIR_RIGHT; 
        }
        if (target_c == col && abs(target_r - row) == 1) {
            map.fixed(r->id);
            // log << "Robot " << id << " fixed " << r.id << "\t("<< r.loc.r << ", " << r.loc.c << ")" << "\t" << map.ded()<< endl;
            return pref_r == -1 ? REPAIR_UP : REPAIR_DOWN; 
        }

        map.update(loc,EMPT);

        if (map.rbots({row + ADJC[0][0],col + ADJC[0][1]}) && map.rbots({row + ADJC[1][0],col + ADJC[1][1]}) && map.rbots({row + ADJC[2][0],col + ADJC[2][1]}) && map.rbots({row + ADJC[3][0],col + ADJC[3][1]})) {
            map.fix(r->loc,r->id, true);
            return REPAIR_UP;
        }

        // if row or col is the same, continue moving in the direction of the broken robot
        //if (pref_r == 0 && map.peek(row + pref_r, col + pref_c).status != ROBOT) {
        if (pref_r == 0 && !map.rbots(row + pref_r, col + pref_c)) {
            return pref_c == -1 ? LEFT : RIGHT;
        }
        else if (pref_r == 0 && map.rbots(row + pref_r, col + pref_c)) {
            map.fix(r->loc,r->id, true);
            goto usual; //return map.in_range(row - 1, col) ? UP : DOWN; 
        }
        //if (pref_c == 0 && map.peek(row + pref_r, col + pref_c).status != ROBOT) {
        if (pref_c == 0 && !map.rbots(row + pref_r, col + pref_c)) {
            return pref_r == -1 ? UP : DOWN;
        }
        else if (pref_c == 0 && map.rbots(row + pref_r, col + pref_c)) {
            map.fix(r->loc,r->id, true);
            goto usual; //return map.in_range(row, col - 1) ? LEFT : RIGHT;
        }

        // chooses the field with debris to move to next
        if (map.peek(row + pref_r, col).status == TRASH) {
            return pref_r == -1 ? UP : DOWN;
        }
        if (map.peek(row, col + pref_c).status == TRASH) {
            return pref_c == -1 ? LEFT : RIGHT;
        }
                
        // choose a random spot
        //if (map.in_range({row + pref_r,col}) && map.peek(row + pref_r, col).status != ROBOT) {
        if (map.in_range({row + pref_r,col}) && !map.rbots(row + pref_r, col)) {
            return pref_r == -1 ? UP : DOWN;
        }
        //if (map.in_range({row,col + pref_c}) && map.peek(row, col + pref_c).status != ROBOT) {
        if (map.in_range({row,col + pref_c}) && !map.rbots(row, col + pref_c)) {
            return pref_c == -1 ? LEFT : RIGHT;
        }

        if (map.in_range({row - pref_r,col}) && !map.rbots(row + pref_r, col)) {
            return pref_r == 1 ? UP : DOWN;
        }
        if (map.in_range({row,col - pref_c}) && !map.rbots(row, col + pref_c)) {
            return pref_c == 1 ? LEFT : RIGHT;
        }
        
        map.fix(r->loc,r->id, true);
        goto usual;
    }
    else if (!comploc(map.robot(id)->target,{-1,-1})) {
        near:
        ERR("Label: near" << std::endl);
        //ERR("near" << std::endl);
        
        if (comploc(map.robot(id)->target,{-1,-1}) || !map.in_range(map.robot(id)->target) || map.peek(map.robot(id)->target).covered || map.peek(map.robot(id)->target).claimed || map.rbots(map.robot(id)->target)) {
            //ERR("in range" << std::endl);
            map.unclaim(id);
            ERR("Goto: usual 939" << std::endl);
            return REPAIR_UP;
        }
        
        //ERR("in range" << std::endl);
        
        Loc target_loc = map.robot(id)->target;
        
        if(map.kernel(target_loc) == 0 || !map.in_range(target_loc)) {
            //ERR("debris" << std::endl);
            map.nearest(id);
            log << map.robot(id)->target.r << ", " << map.robot(id)->target.c << endl;
            ERR("Goto: near 951" << std::endl);
            goto usual;
            //goto usual;
        }
        
        int target_r = target_loc.r;
        int target_c = target_loc.c;

        if (comploc(target_loc,loc) || (target_r == row && abs(target_c - col) == 1) || (target_c == col && abs(target_r - row) == 1)) {
            //ERR("unclaim" << std::endl);
            map.unclaim(id);
            ERR("Goto: usual 962" << std::endl);
            goto usual;
            //return COLLECT;
        }

        int pref_r = target_r < row ? -1 : 1;
        int pref_c = target_c < col ? -1 : 1;
        pref_r = target_r == row ? 0 : pref_r;
        pref_c = target_c == col ? 0 : pref_c;
        
        //ERR("move" << std::endl);
        // preferred directions
        map.update(loc,EMPT);

        // chooses the field with debris to move to next
        if (map.peek(row + pref_r, col).status == TRASH) {
            map.unclaim(id);
            return pref_r == -1 ? UP : DOWN;
        }
        if (map.peek(row, col + pref_c).status == TRASH) {
            map.unclaim(id);
            return pref_c == -1 ? LEFT : RIGHT;
        }
        
        if (pref_r == 0) { //No vertical movement
            return pref_c == -1 ? LEFT : RIGHT;
        }
        if (pref_c == 0) {
            return pref_r == -1 ? UP : DOWN;
        }
        // choose a random spot
        //if (map.in_range({row + pref_r,col}) && map.peek(row + pref_r, col).status != ROBOT) {
        if (map.in_range({row + pref_r,col}) && !map.rbots(row + pref_r, col)) {
            return pref_r == -1 ? UP : DOWN;
        }
        //if (map.in_range({row,col + pref_c}) && map.peek(row, col + pref_c).status != ROBOT) {
        if (map.in_range({row,col + pref_c}) && !map.rbots(row, col + pref_c)) {
            return pref_c == -1 ? LEFT : RIGHT;
        }

        if (map.in_range({row - pref_r,col}) && !map.rbots(row + pref_r, col)) {
            return pref_r == 1 ? UP : DOWN;
        }
        if (map.in_range({row,col - pref_c}) && !map.rbots(row, col + pref_c)) {
            return pref_c == 1 ? LEFT : RIGHT;
        }
        
        switch(rand() % 1) {
		case 0: return pref_r == 1 ? UP : DOWN;
        default: return pref_c == 1 ? LEFT : RIGHT;
		}
    }
    else {
        usual:
        ERR("Label: usual" << endl);
        map.update(loc,EMPT);
        
        if (map.rbots({row + ADJC[0][0],col + ADJC[0][1]}) && map.rbots({row + ADJC[1][0],col + ADJC[1][1]}) && map.rbots({row + ADJC[2][0],col + ADJC[2][1]}) && map.rbots({row + ADJC[3][0],col + ADJC[3][1]})) {
            return REPAIR_UP;
        }

        if ((map.rbots({row + ADJC[0][0],col + ADJC[0][1]}) && map.rbots({row + ADJC[1][0],col + ADJC[1][1]}) && !map.rbots({row + ADJC[2][0],col + ADJC[2][1]}) && map.rbots({row + ADJC[3][0],col + ADJC[3][1]})) || (map.check_l(loc,1,1) > 2 && !map.bots({loc.r, loc.c + 1}))) {
            return RIGHT;
        }
        if ((map.rbots({row + ADJC[0][0],col + ADJC[0][1]}) && !map.rbots({row + ADJC[1][0],col + ADJC[1][1]}) && map.rbots({row + ADJC[2][0],col + ADJC[2][1]}) && map.rbots({row + ADJC[3][0],col + ADJC[3][1]})) || (map.check_r(loc,1,1) > 2 && !map.bots({loc.r, loc.c - 1}))) {
            return LEFT;
        }
        if ((map.rbots({row + ADJC[0][0],col + ADJC[0][1]}) && map.rbots({row + ADJC[1][0],col + ADJC[1][1]}) && map.rbots({row + ADJC[2][0],col + ADJC[2][1]}) && !map.rbots({row + ADJC[3][0],col + ADJC[3][1]})) || (map.check_u(loc,1,1) > 2 && !map.bots({loc.r + 1, loc.c}))) {
            return DOWN;
        }
        if ((!map.rbots({row + ADJC[0][0],col + ADJC[0][1]}) && map.rbots({row + ADJC[1][0],col + ADJC[1][1]}) && map.rbots({row + ADJC[2][0],col + ADJC[2][1]}) && map.rbots({row + ADJC[3][0],col + ADJC[3][1]})) || (map.check_d(loc,1,1) > 2 && !map.bots({loc.r - 1, loc.c}))) {
            return UP;
        }
        
        // set up for kernel checking 
        int check [13] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, ROWS * COLS}; // robots
        int checkd [13] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1}; // debris

        // if it's next to a debris field
        int move = 12;
        int moved = 12;
        for (int i = 0; i < 12; i++) {
            if(map.peek(row + NEIGHBORS[i][0], col + NEIGHBORS[i][1]).status == TRASH && (!map.peek(row + NEIGHBORS[i][0], col + NEIGHBORS[i][1]).claimed || map.peek(row + NEIGHBORS[i][0], col + NEIGHBORS[i][1]).intended == id)) {
                check[i] = map.kernelr({row + (NEIGHBORS[i][0]*4), col + NEIGHBORS[i][1]*4},3);
                checkd[i] = map.kernel({row + (NEIGHBORS[i][0]*4), col + NEIGHBORS[i][1]*4},4);
                if(i > 3 && i < 8) { // diagonal neighbors
                    if ((i == 4 || i == 5) && map.rbots(row + NEIGHBORS[0][0], col + NEIGHBORS[0][1])) { // diagonals up
                        check[i] = -1;
                        checkd[i] = -1;
                        map.treaded({row + NEIGHBORS[i][0], col + NEIGHBORS[i][1]});
                    }
                    if ((i == 6 || i == 7) && map.rbots(row + NEIGHBORS[3][0], col + NEIGHBORS[3][1])) { // diagonals down
                        check[i] = -1;
                        checkd[i] = -1;
                        map.treaded({row + NEIGHBORS[i][0], col + NEIGHBORS[i][1]}); 
                    }
                    map.treaded({row + NEIGHBORS[i][0], col + NEIGHBORS[i][1]},-1); 
                }
                if(i > 7 && map.rbots(row + NEIGHBORS[i - 8][0], col + NEIGHBORS[i - 8][1])) {
                    check[i] = -1;
                    checkd[i] = -1;
                    map.treaded({row + NEIGHBORS[i][0], col + NEIGHBORS[i][1]}); 
                }
            }
            if (map.bots({row + NEIGHBORS[i][0], col + NEIGHBORS[i][1]})) {
                map.treaded({row + NEIGHBORS[i][0], col + NEIGHBORS[i][1]}); 
            }
            
            move = check[i] != -1 && check[i] < check[move] ? i : move;
            moved = checkd[i] != -1 && checkd[i] > checkd[move] ? i : moved;
        }
        
        int yote = 12;
        for (int i = 0; i < 13; i ++) {
            yote = checkd[yote] - (check[yote]) > checkd[i] - (check[i]) && checkd[i] > 0 ? i : yote;
        }
        
        // best of the 2
        if (yote != 12) { 
            //map.nearest(id, {row + NEIGHBORS[yote][0], col + NEIGHBORS[yote][1]});
            ERR("yeet yote throw me off a boat" << std::endl);

            map.nearest(id, {row + NEIGHBORS[yote][0], col + NEIGHBORS[yote][1]});
            goto near;
        }
        
        // less robots 
        if (move != 12) {
            ERR("Damn y'all doing this one huh" << std::endl);
            map.claim(id, {row + NEIGHBORS[move][0], col + NEIGHBORS[move][1]});
            switch(move) {
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
        if (row <= map.b_r() && map.in_range({map.b_r() + 1,col}) && !map.bots({row + 1,col})) {
            return DOWN;
        }
        if (row >= map.b_rb() && map.in_range({map.b_rb() - 1,col}) && !map.bots({row - 1,col})) {
            return UP;
        }
        if (col <= map.b_c() && map.in_range({row,map.b_c() + 1}) && !map.bots({row,col + 1})) {
            return RIGHT;
        }
        if (col >= map.b_cb() && map.in_range({row,map.b_cb() - 1}) && !map.bots({row,col - 1})) {
            return LEFT;
        }

        if (map.kernel(loc,16) == 0 && comploc(map.robot(id)->target,{-1,-1})) {
            Loc save = map.robot(id)->target;
            
            map.nearest(id);
            if (comploc(map.robot(id)->target,save)) {
                return REPAIR_UP;
            }
            ERR(save.r << ":" << save.c << " -> ");
            ERR(map.robot(id)->target.r << ":" << map.robot(id)->target.c << endl);
            log << id << "\t" <<  map.robot(id)->target.r << ", " << map.robot(id)->target.c << endl;
            //ERR(map.robot(id)->target.r << ", " << map.robot(id)->target.c << std::endl);
            ERR("Goto: near 1015" << std::endl);
            goto near;
        }

        ERR("Damn you made it to treaded" << std::endl);
        // choose the least treaded on field
        int best = -1;
        int bestv = ROWS * COLS;
        for (int i = 0; i < 4; i++) {
            if (map.in_range({row + ADJC[i][0],col + ADJC[i][1]}) && !map.rbots({row + ADJC[i][0],col + ADJC[i][1]})) {
                // bonus for previous locations + nearby robots 
                int robonus = comploc(map.peek(row + ADJC[i][0],col + ADJC[i][1]).loc, map.robot(id)->ploc) ? 
                    (NUM * 2) + map.kernelr({row + (ADJC[i][0]*3), col + ADJC[i][1]*3}) - map.kernel({row + (ADJC[i][0]*3), col + ADJC[i][1]*3}) + (map.kernelc({row + (ADJC[i][0]*3), col + ADJC[i][1]*3}) * 2) : 
                    map.kernelr({row + (ADJC[i][0]*3), col + ADJC[i][1]*3}) - map.kernel({row + (ADJC[i][0]*3), col + ADJC[i][1]*3}) + (map.kernelc({row + (ADJC[i][0]*3), col + ADJC[i][1]*3}) * 2);

                // the calculations for least treaded 
                best = map.peek({row + ADJC[i][0],col + ADJC[i][1]}).tread + robonus < bestv ? i : best;
                bestv =  map.peek({row + ADJC[i][0],col + ADJC[i][1]}).tread + robonus < bestv ? map.peek({row + ADJC[i][0],col + ADJC[i][1]}).tread + robonus : bestv;
            }
            else if (row + ADJC[i][0] <= map.b_r() - 1 && !map.bots({row + ADJC[i][0],col + ADJC[i][1]})) {
                return DOWN;
            }
            else if (row + ADJC[i][0] >= map.b_rb() + 1 && !map.bots({row + ADJC[i][0],col + ADJC[i][1]})) {
                return UP;
            }
            else if (col + ADJC[i][1] <= map.b_c() - 1 && !map.bots({row + ADJC[i][0],col + ADJC[i][1]})) {
                return RIGHT;
            }
            else if (col + ADJC[i][1] >= map.b_cb() + 1 && !map.bots({row + ADJC[i][0],col + ADJC[i][1]})) {
                return LEFT;
            }
        }
        
        // if there's no place to go just stay there 
        if (best ==  -1) {
            map.nearest(id);
            goto near;
        }

        switch(best) {
		case 0: return UP;
		case 1: return LEFT;
		case 2: return RIGHT;
		default: return DOWN;
		}
        
        map.nearest(id);
        //ERR(map.robot(id)->target.r << ", " << map.robot(id)->target.c << std::endl);
        //log << id << "\t" <<  map.robot(id)->target.r << ", " << map.robot(id)->target.c << endl;
        goto near;
	}
}

void onRobotMalfunction(int id, Loc loc, Area &area, ostream &log) {
    // map fix function
    map.fix(loc,id);
    //log << "Robot " << map.locate(id).fixer << " to fix " << id << "\t("<< loc.r << ", " << loc.c << ")" << "\t" << map.ded()<< endl;
}

void onClockTick(int time, ostream &log) {
	if (time % 50 == 0) {
        //log << time << "\t" << map.b_r() << ", " << map.b_c() << "\t" << map.b_rb() << ", " << map.b_cb()<< "\t" <<  map.clear() << " / " << map.pile() << endl;
    }
    
}
