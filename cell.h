#ifndef _CELL_H_
#define _CELL_H_

#include <string>
#include <memory>

class Block;

class Cell {
    public:
        Cell(int row, int col, char type = ' ', Block *b = nullptr, bool occupied = false);
        bool isOccupied();
        char getBlockType();
        Block *getBlock();
        void updateCell();
        void setBlockPtr(Block *b);
        void setCol(int c);
        void setRow(int r);
        bool getIsBlind();
        void setBlind();
        void unSetBlind();
    private:
        int row;
        int col;
        char blockType; 
        Block *block;
        bool occupied;
        bool isBlind = false;
};

#endif
