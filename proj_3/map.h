
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
};

class Map {
    std::vector<std::vector <Field> > field;
    //std::vector<std::vector <Places> > fields;
    //std::vector<std::vector <bool> > covered;
    std::vector<Loc> robots; 
    int ROWS;
    int COLS;
    int NUM;
    int BOUND_R = 0;
    int BOUND_C = 0;
    int BOUND_RB;
    int BOUND_CB;
    int cleared = 0;
    int piles; 
    //std::vector<std::vector<int>> TREAD;
    //std::vector<std::vector<int>> DEAD;

public:
    Map (int row, int col, int num);
    bool in_range (Loc loc);
    bool in_og_range (Loc loc);
    Field peek (int row, int col);
    Field peek (Loc loc);
    bool update (Loc loc, Places p);
    bool update (Loc loc, Places p, int id);
    int tread (Loc loc);
    int dead (Loc loc);
    void treaded (Loc loc);
    void deaded (Loc loc);
    Loc locate (int id);
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
