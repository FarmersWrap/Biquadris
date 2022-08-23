#include "cell.h"
#include "block.h"

using namespace std;

Cell::Cell(int row, int col, char type, Block *b, bool occupied):
row{row}, col{col}, blockType{type}, block{b}, occupied{occupied} {}

bool Cell::isOccupied() {
    return occupied;
}

char Cell::getBlockType() {
    return blockType;
}

Block *Cell::getBlock() {
    return block;
}

void Cell::setBlockPtr(Block *b) {
    if (b == nullptr) {
        occupied = false;
    } else {
        occupied = true;
        blockType = b->getType();
    }
    block = b;
}

void Cell::setCol(int c) {
    col = c;
}
void Cell::setRow(int r) {
    row = r;
}

void Cell::setBlind() {
    isBlind = true;
}

void Cell::unSetBlind() {
    isBlind = false;
}

bool Cell::getIsBlind() {
    return isBlind;
}
