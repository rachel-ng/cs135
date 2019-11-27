#include "map.h"

const int NEIGHBORS[12][2] = {{-1,0},{0,-1},{0,1},{1,0},{-1,-1},{-1,1},{1,-1},{1,1},{-2,0},{0,-2},{0,2},{2,0}};

Map::Map (int row, int col, int num) {
    ROWS = row;
    COLS = col;
    NUM = num;
    piles = ROWS * COLS;
    robots.resize(NUM);
    fields.resize(ROWS, std::vector<Places>(COLS,UNDEF));
    covered.resize(ROWS, std::vector<bool>(COLS,false));
    TREAD.resize(ROWS, std::vector<int>(COLS,0));
    DEAD.resize(ROWS, std::vector<int>(COLS,0));
}

bool Map::in_range (Loc loc) {
  return (loc.r >= BOUND_R && loc.c >= BOUND_C && loc.r < ROWS && loc.c < COLS);
}

Places Map::peek (int row, int col) {
    Loc loc = {row,col};
    if (in_range(loc)) {
        return fields[row][col];
    }
    return UNDEF;
}

Places Map::peek (Loc loc) {
    if (in_range(loc)) {
        return fields[loc.r][loc.c];
    }
    return UNDEF;
}
    
bool Map::update (Loc loc, Places p) {
    if (in_range(loc)) {
        Places prev = fields[loc.r][loc.c];
        fields[loc.r][loc.c] = p;
        if (p == TRASH) {
            cleared += 1;
            TREAD[loc.r][loc.c] -= 1;
            for (int i = 0; i < 8; i++) {
                if(in_range({loc.r + NEIGHBORS[i][0],loc.c + NEIGHBORS[i][1]})) {
                    TREAD[loc.r + NEIGHBORS[i][0]][loc.c + NEIGHBORS[i][1]] -= 1;
                }
            }
        }
        if (prev == TRASH) {
            cleared -= 1;
            TREAD[loc.r][loc.c] = 1;
            DEAD[loc.r][loc.c] = 1;
        }
        if (p == EMPT) {
            covered[loc.r][loc.c] = true;
            DEAD[loc.r][loc.c] += 1;
            TREAD[loc.r][loc.c] += 1;
        }
        //bound();
        //bound_r();
        //bound_c();
        if(loc.r > BOUND_R) {
            bound_r(); 
        }
        if(loc.c > BOUND_C) {
            bound_c();
        }

        return true;
    }
    return false;
}

bool Map::update (Loc loc, Places p, int id) {
    if (in_range(loc)) {
        Places prev = fields[loc.r][loc.c];
        fields[loc.r][loc.c] = p;
        if (p == TRASH) {
            cleared += 1;
            TREAD[loc.r][loc.c] -= 1;
            for (int i = 0; i < 12; i++) {
                if(in_range({loc.r + NEIGHBORS[i][0],loc.c + NEIGHBORS[i][1]})) {
                    TREAD[loc.r + NEIGHBORS[i][0]][loc.c + NEIGHBORS[i][1]] -= 1;
                }
            }
        }
        if (prev == TRASH) {
            cleared -= 1;
            TREAD[loc.r][loc.c] = 1;
            DEAD[loc.r][loc.c] = 1;
        }
        if (p == EMPT) {
            covered[loc.r][loc.c] = true;
            DEAD[loc.r][loc.c] += 1;
            TREAD[loc.r][loc.c] += 1;
        }
        else if (p == ROBOT) {
            robots[id] = loc;
            TREAD[loc.r][loc.c] += 1;
            DEAD[loc.r][loc.c] += 1;
        }
        if(loc.r > BOUND_R) {
            bound_r(); 
        }
        if(loc.c > BOUND_C) {
            bound_c();
        }
        return true;
    }
    return false;
}

int Map::tread (Loc loc) {
    return TREAD[loc.r][loc.c];
}

int Map::dead (Loc loc) {
    return DEAD[loc.r][loc.c];
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
    for (int i = BOUND_R; i < ROWS; i++) {
        bool rip = true;
        for (int c = BOUND_C; c < COLS; c++) {
            if (!covered[i][c]) {
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
    for (int i = BOUND_C; i < COLS; i++) {
        bool rip = true;
        for (int r = BOUND_R; r < ROWS; r++) {
            if (!covered[r][i]) {
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
/*
void Map::bound_rb() {
    for (int i = BOUND_R; i < ROWS; i++) {
        bool rip = true;
        for (int c = BOUND_C; c < COLS; c++) {
            if (!covered[i][c]) {
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

void Map::bound_cb() {
    for (int i = BOUND_CB; i > BOUND_C; i++) {
        bool rip = true;
        for (int r = BOUND_R; r < BOUND_RB; r++) {
            if (!covered[r][i]) {
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
}*/
/*int Map::bound_c() {
    for (int i = BOUND_C + 1; i < COLS; i++) {
        if (!all_ded_c[i]) {
            BOUND_C = i - 1;
            break;
        }
    }
}*/
int Map::b_r() {
    return BOUND_R;
}

int Map::b_c() {
    return BOUND_C;
}

