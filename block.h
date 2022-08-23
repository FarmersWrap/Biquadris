#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <utility>
#include <vector>
#include "grid.h"
#include "cell.h"

class Block {
    public:
        Block(int level, int gravity, int row = 3, int col = 0, int state = 0);
        char getType();
        int getLevel();
        int getRow();
        int getCol();
        int getState();
        void addElim();
        int getElim();
        int getGravity();
        void setGravity(int gravity);
        bool canSet(Grid *g);
        bool moveLeft(Grid *g);
        bool moveRight(Grid *g);
        bool moveDown(Grid *g);
        bool rotateLeft(Grid *g);
        bool rotateRight(Grid *g);
        bool drop(Grid *g);
        virtual std::vector<std::pair<int, int>> getCoord() = 0;
    protected: 
        char type;
        int level;
        int gravity;
        int row;
        int col;
        int state;
        int eliminated = 0;
        std::vector<std::pair<int, int>> initialPairs();
        bool checkCells(Grid *g);
};

#endif
