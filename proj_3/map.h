
#ifndef MAP_H
#define MAP_H

#include <vector>
#include "common.h"

enum Places {EMPT, TRASH, UNDEF, ROBOT, DED};
class Map {
    std::vector<std::vector <Places> > fields;
    std::vector<std::vector <bool> > covered;
    std::vector<Loc> robots; 
    int ROWS;
    int COLS;
    int NUM;
    int BOUND_R = 0;
    int BOUND_C = 0;
    int cleared = 0;
    int piles; 
    std::vector<std::vector<int>> TREAD;
    std::vector<std::vector<int>> DEAD;

public:
    Map (int row, int col, int num);
    bool in_range (Loc loc);
    Places peek (int row, int col);
    Places peek (Loc loc);
    bool update (Loc loc, Places p);
    bool update (Loc loc, Places p, int id);
    int tread (Loc loc);
    int dead (Loc loc);
    Loc locate (int id);
    int clear ();
    int pile ();
    void bound();
    int b_r();
    int b_c();
};

#endif
