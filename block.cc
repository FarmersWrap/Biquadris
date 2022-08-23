#include "block.h"
#include <iostream>

using namespace std;

Block::Block(int level, int gravity, int row, int col, int state):
level{level}, gravity{gravity}, row{row}, col{col}, state{state} {}

char Block::getType() {
    return type;
}

int Block::getState() {
    return state;
}

int Block::getLevel() {
    return level;
}

int Block::getRow() {
    return row;
}

int Block::getCol() {
    return col;
}

int Block::getGravity() {
    return gravity;
}

std::vector<std::pair<int, int>> Block::initialPairs() {
    vector<pair<int, int>> vec;
    for (int i = 0; i < 4; i++) {
       vec.emplace_back(pair<int, int> {row, col});
    }
    return vec;
}

bool Block::checkCells(Grid *g) {
    vector<pair<int, int>> vec = getCoord();

    for (int i = 0; i < 4; i++) {
        if (vec[i].first > 17 || vec[i].second > 10 ||
            vec[i].first < 0 || vec[i].second < 0 || 
            g->getCell(vec[i].first, vec[i].second).isOccupied()) {
                return false;
            }
    }
    return true;
}

bool Block::canSet(Grid *g) {
    return checkCells(g);
}

bool Block::rotateLeft(Grid *g) {
    state += 3;
    if (checkCells(g)) return true;
    ++state;
    return false;
}

bool Block::rotateRight(Grid *g) {
    state += 1;
    if (checkCells(g)) return true;
    --state;
    return false;
}

bool Block::moveLeft(Grid *g) {
    --col;
    if(checkCells(g)) return true;
    ++col;
    return false;
}

bool Block::moveRight(Grid *g) {
    ++col;
    if(checkCells(g)) return true;
    --col;
    return false;
}

bool Block::moveDown(Grid *g) {
    ++row;
    if(checkCells(g)) return true;
    --row;
    return false;
}

bool Block::drop(Grid *g) {
    int i = 3;
    while(moveDown(g)) {
        i++;
    }
    return true;
}

void Block::addElim() {
    eliminated += 1;
}

int Block::getElim() {
    return eliminated;
}

void Block::setGravity(int gravity) {
    this->gravity += gravity;
}
