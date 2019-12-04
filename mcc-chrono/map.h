
#ifndef MAP_H
#define MAP_H

#include <vector>
#include "common.h"

enum Places {EMPT, TRASH, UNDEF, ROBOT, DED};

class Field {
public:
    Places status;
    bool covered;
    int tread;
    int dead;
    int robot;
};

class Robot {
public:
    Loc loc = {-1,-1};
    bool dead = false;
    int id;
    int fixer = -1;
    
    Robot (int i) {
        id = i;
    }
    
    int fixing = -1;
        void update (Loc l) {
        loc = l;
    }
    
    void update (Loc l, bool d) {
        loc = l;
        dead = d;
    }
};



class Map {
    std::vector<std::vector <Field> > fields;
    std::vector<Robot> robots; 
    int ROWS;
    int COLS;
    int NUM;
    int BOUND_R = 0;
    int BOUND_C = 0;
    int BOUND_RB;
    int BOUND_CB;
    int cleared = 0;
    int def_clear = 0;
    int piles; 

public:
    Map (int row, int col, int num);
    bool in_og_range (Loc loc);
    bool in_og_range (int r, int c);
    bool in_range (Loc loc);
    bool in_range (int r, int c);
    Robot locate (int id);
    Field peek (int row, int col);
    Field peek (Loc loc);
    bool update (Loc loc, Places p);
    bool update (Loc loc, Places p, int id);
    void treaded (Loc loc);
    void deaded (Loc loc);
    void set_default();
    void fixer (int id, int fix);
    void fixed (int id);
    int clear ();
    int pile ();
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

#endif
