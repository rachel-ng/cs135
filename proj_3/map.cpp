#include "map.h"

double manhattanDist(Loc start, Loc target) {
    return abs(start.c-target.c) + abs(start.r-target.r);
}

bool comploc (Loc a, Loc b) {
    if (a.r == b.r && a.c == b.c) {
        return true;
    }
    return false;
}

Map::Map (int row, int col, int num) {
    ROWS = row;
    COLS = col;
    NUM = num;
    BOUND_CB  = COLS;
    BOUND_RB = ROWS;
    piles = ROWS * COLS;
    fields.resize(ROWS, std::vector<Field>(COLS, {UNDEF,{-1,-1},false,0,0,-1}));
    robots.resize(NUM,Robot(-1));
    for (int i = 0; i < NUM; i++) {
        robots[i] = Robot(i);
    }
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

int Map::kernel (Loc loc) {
    int yeet = 0;
    //int row = (loc.r >= BOUND_R) ? (loc.r > map.b_rb()) ? map.b_rb() : loc.r : map.b_r();
    int row = (loc.r >= BOUND_R) ? (loc.r > BOUND_RB) ? BOUND_RB : loc.r : BOUND_R;
    int col = (loc.c >= BOUND_C) ? (loc.c > BOUND_CB) ? BOUND_CB : loc.c : BOUND_C;

    for (int r = -3; r < 3; r++) {
        for (int c = -3; c < 3; c++) {
            if(in_og_range(row + r, col + c)) {
                if (peek(row + r, col + c).status == TRASH) {
                    yeet += 1;
                }
            }
        }
    }
    return yeet;
}

int Map::kernel (Loc loc, int size) {
    int yeet = 0;
    //int row = (loc.r >= BOUND_R) ? (loc.r > map.b_rb()) ? map.b_rb() : loc.r : map.b_r();
    int row = (loc.r >= BOUND_R) ? (loc.r > BOUND_RB) ? BOUND_RB : loc.r : BOUND_R;
    int col = (loc.c >= BOUND_C) ? (loc.c > BOUND_CB) ? BOUND_CB : loc.c : BOUND_C;

    for (int r = -size; r < size; r++) {
        for (int c = -size; c < size; c++) {
            if(in_og_range(row + r, col + c)) {
                if (peek(row + r, col + c).status == TRASH) {
                    yeet += 1;
                }
            }
        }
    }
    return yeet;
}

int Map::kernel (int row, int col) {
    int yeet = 0;
    for (int r = -3; r < 3; r++) {
        for (int c = -3; c < 3; c++) {
            if(in_og_range(row + r, col + c)) {
                if (peek(row + r, col + c).status == TRASH) {
                    yeet += 1;
                }
            }
        }
    }
    return yeet;
}

int Map::kernel (int row, int col, int size) {
    int yeet = 0;
    for (int r = -size; r < size; r++) {
        for (int c = -size; c < size; c++) {
            if(in_og_range(row + r, col + c)) {
                if (peek(row + r, col + c).status == TRASH) {
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
            /*for (int i = 0; i < 12; i++) {
                if(in_og_range({loc.r + NEIGHBORS[i][0],loc.c + NEIGHBORS[i][1]})) {
                    fields[loc.r + NEIGHBORS[i][0]][loc.c + NEIGHBORS[i][1]].tread -= 1;
                }
            }*/
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
        else if (p == ROBOT) {
            robots[id].update(loc);
            fields[loc.r][loc.c].tread += 2;
            fields[loc.r][loc.c].dead += 1;
            fields[loc.r][loc.c].robot = id;
        }
        else if (p == DED) {
            robots[id].update(loc, true);
            fields[loc.r][loc.c].robot= id;
            dead.push_back(id);
        }

        if (p!= TRASH && (loc.r <= BOUND_R || loc.c <= BOUND_C || loc.r > BOUND_RB || loc.c > BOUND_CB)) { 
            fields[loc.r][loc.c].tread += 1;
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

void Map::fix () {
    for (int i = 0; i < dead.size(); i++) {
        if (locate(dead[i]).fixer == -1) {
            fix(locate(dead[i]).loc, dead[i]);
        }
    }
}

void Map::fix (Loc loc, int id) {
    if (locate(id).fixer != -1) {
        return;
    }
    update(loc,DED,id);
    if (locate(id).fixing != -1) {
        fix(locate(id).loc, locate(id).fixing);
    }
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
    if (f == -1) {
        return;
    }
    else {
        fixer(id,f);
	}
} 

void Map::fixer (int id, int fix) {
    robots[id].fixer = fix;
    robots[fix].fixing = id;
    broken += 1;
}

void Map::fixed (int id) {
    int fix = robots[id].fixer;
    robots[fix].fixing = -1;
    robots[id].fixer = -1;
    robots[id].dead = false;
    broken -= 1;
    if (dead.size() > 1) {;
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
}

bool Map::bots(Loc loc) {
    return (peek(loc).status != ROBOT || peek(loc).status != DED);
}

bool Map::bots(int row, int col) {
    return in_og_range(row,col) ? (peek(row,col).status != ROBOT || peek(row,col).status != DED) : false;
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

void Map::bound_r() {
    bool rip = true;
    for (int i = BOUND_R; i < BOUND_RB; i++) {
        for (int c = BOUND_C; c < BOUND_CB; c++) {
            if (!fields[i][c].covered) {
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
            if (!fields[r][i].covered) {
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
            if (!fields[i][c].covered) {
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
            if (!fields[r][i].covered) {
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
