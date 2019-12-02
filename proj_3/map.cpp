#include "map.h"

const int NEIGHBORS[12][2] = {{-1,0},{0,-1},{0,1},{1,0},{-1,-1},{-1,1},{1,-1},{1,1},{-2,0},{0,-2},{0,2},{2,0}};

Map::Map (int row, int col, int num) {
    ROWS = row;
    COLS = col;
    NUM = num;
    BOUND_CB  = COLS;
    BOUND_RB = ROWS;
    piles = ROWS * COLS;
    robots.resize(NUM);
    field.resize(ROWS, std::vector<Field>(COLS,{UNDEF,false,0,0}));
    //fields.resize(ROWS, std::vector<Places>(COLS,UNDEF));
    //covered.resize(ROWS, std::vector<bool>(COLS,false));
    //TREAD.resize(ROWS, std::vector<int>(COLS,0));
    //DEAD.resize(ROWS, std::vector<int>(COLS,0));
}

bool Map::in_og_range (Loc loc) {
  return (loc.r >= 0 && loc.c >= 0 && loc.r < ROWS && loc.c < COLS);
}

bool Map::in_range (Loc loc) {
  return (loc.r >= BOUND_R && loc.c >= BOUND_C && loc.r < BOUND_RB && loc.c < BOUND_CB);
}


Field Map::peek (int row, int col) {
    Loc loc = {row,col};
    if (in_range(loc)) {
        //return fields[row][col];
        return field[row][col];
    }
    return {UNDEF,false,-1,-1};
}

Field Map::peek (Loc loc) {
    if (in_range(loc)) {
        //return fields[loc.r][loc.c];
        return field[loc.r][loc.c];
    }
    return {UNDEF,false,-1,-1};
}   
bool Map::update (Loc loc, Places p) {
    if (in_range(loc)) {
        //Places prev = fields[loc.r][loc.c];
        Places prev = field[loc.r][loc.c].status;
        //fields[loc.r][loc.c] = p;
        field[loc.r][loc.c].status = p;
        if (p == TRASH) {
            cleared += 1;
            //TREAD[loc.r][loc.c] -= 1;
            field[loc.r][loc.c].tread -= 1;
            for (int i = 0; i < 8; i++) {
                if(in_range({loc.r + NEIGHBORS[i][0],loc.c + NEIGHBORS[i][1]})) {
                    //TREAD[loc.r + NEIGHBORS[i][0]][loc.c + NEIGHBORS[i][1]] -= 1;
                    field[loc.r + NEIGHBORS[i][0]][loc.c + NEIGHBORS[i][1]].tread -= 1;
                }
            }
        }
        if (prev == TRASH) {
            cleared -= 1;
            //TREAD[loc.r][loc.c] = 0;
            //DEAD[loc.r][loc.c] = 1;
            field[loc.r][loc.c].tread = 0;
            field[loc.r][loc.c].dead = 1;
        }
        if (p == EMPT) {
            //covered[loc.r][loc.c] = true;
            field[loc.r][loc.c].covered = true;
            //DEAD[loc.r][loc.c] += 1;
            //TREAD[loc.r][loc.c] += 1;
            field[loc.r][loc.c].dead += 1;
            field[loc.r][loc.c].tread += 1;
        }
        
        if (p!= TRASH && (loc.r <= BOUND_R || loc.c <= BOUND_C || loc.r > BOUND_RB || loc.c > BOUND_CB)) { 
            //TREAD[loc.r][loc.c] += 1;
            field[loc.r][loc.c].tread += 1;
            return true;
        }
        
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
        Places prev = field[loc.r][loc.c].status;
        //fields[loc.r][loc.c] = p;
        field[loc.r][loc.c].status = p;
        if (p == TRASH) {
            cleared += 1;
            //TREAD[loc.r][loc.c] -= 1;
            field[loc.r][loc.c].tread -= 1;
            for (int i = 0; i < 12; i++) {
                if(in_og_range({loc.r + NEIGHBORS[i][0],loc.c + NEIGHBORS[i][1]})) {
                    //TREAD[loc.r + NEIGHBORS[i][0]][loc.c + NEIGHBORS[i][1]] -= 1;
                    field[loc.r + NEIGHBORS[i][0]][loc.c + NEIGHBORS[i][1]].tread -= 1;
                }
            }
        }

        if (prev == TRASH) {
            cleared -= 1;
            //TREAD[loc.r][loc.c] = 0;
            //DEAD[loc.r][loc.c] = 1;
            field[loc.r][loc.c].tread = 0;
            field[loc.r][loc.c].dead = 1;
        }
        if (p == EMPT) {
            //covered[loc.r][loc.c] = true;
            field[loc.r][loc.c].covered = true;
            //DEAD[loc.r][loc.c] += 1;
            //TREAD[loc.r][loc.c] += 1;
            field[loc.r][loc.c].dead += 1;
            field[loc.r][loc.c].tread += 1;
        }
        else if (p == ROBOT) {
            robots[id] = loc;
            //TREAD[loc.r][loc.c] += 1;
            //DEAD[loc.r][loc.c] += 1;
            field[loc.r][loc.c].dead += 1;
            field[loc.r][loc.c].tread += 1;
        }
        
        //if (loc.r <= BOUND_R || loc.c <= BOUND_C || loc.r > BOUND_RB || loc.c > BOUND_CB) { 

        if (p!= TRASH && (loc.r <= BOUND_R || loc.c <= BOUND_C || loc.r > BOUND_RB || loc.c > BOUND_CB)) { 
            //TREAD[loc.r][loc.c] += 1;
            field[loc.r][loc.c].tread += 1;
            return true;
        }

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

int Map::tread (Loc loc) {
    //return TREAD[loc.r][loc.c];
    return field[loc.r][loc.c].tread;
}

int Map::dead (Loc loc) {
    //return DEAD[loc.r][loc.c];
    return field[loc.r][loc.c].dead;
}

void Map::treaded (Loc loc) {
    //TREAD[loc.r][loc.c] += 1;
    field[loc.r][loc.c].tread += 1;
}

void Map::deaded (Loc loc) {
    //DEAD[loc.r][loc.c] += 1;
    field[loc.r][loc.c].dead += 1;
}

Loc Map::locate (int id) {
    return robots[id];
}

int Map::clear () {
    return cleared;
}

int Map::pile () {
    return piles;
}

void Map::bound_r() {
    bool rip = true;
    for (int i = BOUND_R; i < BOUND_RB; i++) {
        for (int c = BOUND_C; c < BOUND_CB; c++) {
            //if (!covered[i][c]) {
            if (!field[i][c].covered) {
                rip = false;
                break;
            }
        }
        if (rip) {
            BOUND_R = i;
        }
        else {
            break;
        }
    }
}

void Map::bound_c() {
    bool rip = true;
    for (int i = BOUND_C; i < BOUND_CB; i++) {
        for (int r = BOUND_R; r < BOUND_RB; r++) {
            //if (!covered[r][i]) {
            if (!field[r][i].covered) {
                rip = false;
                break;
            }
        }
        if (rip) {
            BOUND_C = i;
        }
        else {
            break;
        }
    }
}

void Map::bound_rb() {
    for (int i = BOUND_RB-1; i >= BOUND_R; i--) {
        bool rip = true;
        for (int c = BOUND_C; c < BOUND_CB; c++) {
            //if (!covered[i][c]) {
            if (!field[i][c].covered) {
                rip = false;
                break;
            }
        }
        if (rip) {
            BOUND_RB = i;
        }
        else {
            break;
        }
    }
}

void Map::bound_cb() {
    for (int i = BOUND_CB-1; i >= BOUND_C; i--) {
        bool rip = true;
        for (int r = BOUND_R; r < BOUND_RB; r++) {
            //if (!covered[r][i]) {
            if (!field[r][i].covered) {
                rip = false;
                break;
            }
        }
        if (rip) {
            BOUND_CB = i;
        }
        else {
            break;
        }
    }
}

int Map::b_r() {
    return BOUND_R;
}

int Map::b_c() {
    return BOUND_C;
}

int Map::b_rb() {
    return BOUND_RB;
}

int Map::b_cb() {
    return BOUND_CB;
}
