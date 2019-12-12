#include <cmath>
#include "map.h"

const int ADJC[4][2] = {{-1,0},{0,-1},{0,1},{1,0}};

double manhattanDist(Loc start, Loc target) { // manhattan distance 
    return abs(start.c-target.c) + abs(start.r-target.r);
}

bool comploc (Loc a, Loc b) { // compare locations 
    return (a.r == b.r && a.c == b.c) ? true : false;
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
    fields.resize(ROWS, std::vector<Field>(COLS, {UNDEF,{-1,-1},false,0,0,-1}));
    robots.resize(NUM,Robot(-1));
    for (int i = 0; i < NUM; i++) {
        robots[i] = Robot(i);
    }
    RSIZE = ROWS / NUMRT;
    CSIZE = COLS / NUMRT;
    KSIZE = RSIZE > CSIZE ? RSIZE : CSIZE;
    claim.resize(RSIZE * CSIZE + 1,false);
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

Field Map::peek (int row, int col) {
    Loc loc = {row,col};
    if (in_og_range(loc)) {
        return fields[row][col];
    }
    return {UNDEF, {-1,-1},  false, -1, -1, -1};
}

Field Map::peek (Loc loc) {
    if (in_og_range(loc)) {
        return fields[loc.r][loc.c];
    }
    return {UNDEF, {-1,-1}, false, -1, -1, -1};
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
        if (locate(dead[i]).fixer == -1) {
            fix(locate(dead[i]).loc, dead[i]);
            return;
        }
    }
}

void Map::fix (Loc loc, int id) { // fix a robot 
    if (locate(id).fixer != -1) {
        return;
    }
    // change status to dead
    update(loc,DED,id);
    if (locate(id).fixing != -1) { // assigns new fixer to the robot this was supposed to be fixing (if available)
        fix(locate(id).loc, locate(id).fixing);
    }
    // find closest robot and assign to fix this one 
    int min = ROWS * COLS;
    int f = -1;
    for (int i = 0; i < NUM; i++) {
        if (i != id && locate(i).fixing == -1 && !locate(i).dead) {
            if (manhattanDist(loc, locate(i).loc) < min) {
                min = manhattanDist(loc, locate(i).loc);
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
    if (locate(id).fixer != -1 && !force) {
        return;
    }
    if (locate(id).fixer != -1 && force) {
        robots[locate(id).fixer].fixing = -1; 
    }
    // change status to dead
    update(loc,DED,id);
    if (locate(id).fixing != -1) { // assigns new fixer to the robot this was supposed to be fixing (if available)
        fix(locate(id).loc, locate(id).fixing);
    }
    // find closest robot and assign to fix this one 
    int min = ROWS * COLS;
    int f = -1;
    for (int i = 0; i < NUM; i++) {
        if (i != id && locate(i).fixing == -1 && !locate(i).dead) {
            if (manhattanDist(loc, locate(i).loc) < min) {
                min = manhattanDist(loc, locate(i).loc);
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
    /*double b[5] = {manhattanDist({BOUND_R - loc.r,BOUND_C - loc.c},loc), manhattanDist({BOUND_RB - loc.r,BOUND_C - loc.c},loc), manhattanDist({BOUND_R - loc.r,BOUND_CB - loc.c},loc), manhattanDist({BOUND_RB - loc.r,BOUND_CB - loc.c},loc), ROWS * COLS * 1.1};
    Loc l[5] = {{BOUND_R + 4, BOUND_C + 4}, {BOUND_R + 4, BOUND_CB - 4}, {BOUND_RB - 4, BOUND_C + 4}, {BOUND_RB - 4, BOUND_CB - 4}, {BOUND_R + 4, BOUND_C + 4}};
    int k[5] = {kernel(l[0],5),kernel(l[1],5),kernel(l[2],5),kernel(l[3],5), -10000};
    int best = 4;
    for (int i = 1; i < 4; i++) {
        best = b[best] < b[i] && k[i] > k[best]? i : best;
    }*/
    Loc best = loc;
    int bestd = RSIZE * CSIZE;
    int bestk = -1000;
    for (int r = BOUND_R; r < BOUND_RB; r++) {
        for (int c = BOUND_C; c < BOUND_CB; c++) {
            if (in_range(r,c)) {
                Loc l = {r,c};
                best = fields[r][c].covered && bestd > manhattanDist(loc,l) && bestk > kernel(l) - kernelr(l) ? l : best;
            }
        }
    }
    robots[id].target = best;
}

void Map::unclaim (int id) {
    robots[id].target = {-1,-1};
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
