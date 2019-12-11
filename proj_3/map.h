
#ifndef MAP_H
#define MAP_H

#include <vector>
#include "common.h"

enum Places {EMPT, TRASH, UNDEF, ROBOT, DED};

class Field {
public:
    Places status;
    Loc loc;
    bool covered;
    int tread;
    int dead;
    int robot;
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
    
    Robot (int i) { // set up robots 
        id = i;
    }
    
    void update (Loc l) { 
        ploc = loc;
        loc = l;
    }
    
    void update (Loc l, bool d) {
        ploc = loc;
        loc = l;
        dead = d;
    }
    
    int fixers () {
        return fixer;
    }

    int fixings () {
        return fixing;
    }
};

class Map {
    std::vector<std::vector <Field> > fields;
    std::vector<Robot> robots; 
    std::vector<int> dead; 
    int ROWS;
    int COLS;
    int NUM;
    int NUMRT;
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

double manhattanDist(Loc,Loc);
bool comploc(Loc,Loc);

#endif
