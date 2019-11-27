#include "map.h"

Map::Map (int row, int col, int num) {
    ROWS = row;
    COLS = col;
    NUM = num;
    piles = ROWS * COLS;
    robots.resize(NUM);
    fields.resize(ROWS, std::vector<Places>(COLS,UNDEF));
    covered.resize(NUM, std::vector<bool>(COLS,false));
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
        }
        if (p == EMPT && prev == TRASH) {
            cleared -= 1;
            covered[loc.r][loc.c] = true;
            DEAD[loc.r][loc.c] += 1;
            TREAD[loc.r][loc.c] += 1;
        }
        else if (p == EMPT) {
            DEAD[loc.r][loc.c] += 1;
            TREAD[loc.r][loc.c] += 1;
        }
        return true;
    }
    return false;
}

bool Map::update (Loc loc, Places p, int id) {
    if (in_range(loc)) {
        Places prev = fields[loc.r][loc.c];
        fields[loc.r][loc.c] = p;
        
        if (p == ROBOT) {
            robots[id] = loc; 
            covered[loc.r][loc.c] = true;
            TREAD[loc.r][loc.c] += 1;
        }
        return true;
    }
    return false;
}

int Map::tread (Loc loc) {
    return TREAD[loc.r][loc.c];
}

Loc Map::locate (int id) {
    return robots[id];
}



