#include <iostream>
#include <math.h>
#include "panel.h"
#include "score.h"
#include "level.h"
#include "grid.h"
#include "block.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "TBlock.h"
#include "OBlock.h"
#include "IBlock.h"
#include "ZBlock.h"
#include "SBlock.h"
#include "JBlock.h"
#include "LBlock.h"
#include "starBlock.h"

using namespace std;

static const int GameOver = -1;
static const int NotSwitchPlayer = 0;
static const int SwitchPlayer = 1;
static const int forceRestart = 2;
static const int runSeq = 3;

// *******************************************************
// *********************** Public ************************
// *******************************************************

Panel::Panel(int startLevel, int seed, string file, string file34, int hiScore) : 
Subject{}, currLevel{startLevel}, seed{seed}, fileForLevel0{file}, fileForLevel34{file34}, hiScore{hiScore} {
    score = make_unique<Score>(0, hiScore, 0);
    level = generateLevel();
    grid = make_unique<Grid>();    
    blocks.emplace_back(level->generateBlock());
    currBlock = blocks.back().get();
    blocks.emplace_back(level->generateBlock());
    nextBlock = blocks.back().get();
    setBlock();
}

Panel::~Panel() {}

Level *Panel::getLevelPtr() {
    return level.get();
}

Score *Panel::getScorePtr() {
    return score.get();
}

Grid *Panel::getGridPtr() {
    return grid.get();
}

Block *Panel::getCurrBlockPtr() {
    return currBlock;
}

Block *Panel::getNextBlockPtr() {
    return nextBlock;
}

int Panel::moveBlock(bool toLeft, int down, int multiplier) {
    unSetGrid();
    for (int i = 0; i < multiplier; i++){
        if (toLeft) {
            currBlock->moveLeft(grid.get());
        } else {
            currBlock->moveRight(grid.get());
        }
    }
    for (int i = 0; i < down; i++) {
        currBlock->moveDown(grid.get());
    }
    int gravity = currBlock->getGravity();
    for (int i = 0; i < gravity; i++) {
        if (!currBlock->moveDown(grid.get())) {
            return dropBlock();
        }
    }
    setBlock();
    notifyObservers();
    return NotSwitchPlayer;
}

int Panel::rotateBlock(bool clockwise, int multiplier) {
    unSetGrid();
    for (int i = 0; i < multiplier; i++){
        if (clockwise) {
            currBlock->rotateRight(grid.get());
        } else {
            currBlock->rotateLeft(grid.get());
        }
    }
    int gravity = currBlock->getGravity();
    for (int i = 0; i < gravity; i++) {
        if (!currBlock->moveDown(grid.get())) {
            return dropBlock();
        }
    }
    setBlock();
    notifyObservers();
    return NotSwitchPlayer;
}

int Panel::dropBlock() {
    unSetGrid();
    currBlock->drop(grid.get());
    setBlock();
    if (level->getLevel() == 4) {
        level4drop += 1;
    }
    if (level4drop % 5 == 0 && level4drop > 0 && level->getLevel() == 4) {
        dropStar();
    }
    int clearedRows = 0;
    clearRows(clearedRows);
    if (clearedRows >= 1) {
        score->update(pow((clearedRows + level->getLevel()), 2), getBlockScore());
    }
    if (clearedRows >= 2) {
        specialAction = true;
    }
    blocks.emplace_back(level->generateBlock());
    currBlock = nextBlock;
    nextBlock = blocks.back().get();

    bool isSet = setBlock();

    unBlind();
    notifyObservers();
    if (!isSet) {
        return GameOver;
    }
    return SwitchPlayer;
}

///////////////////////// Notice /////////////////////////
//  These two function can only be called if currBlock  //
//  is legal, otherwise the currBlock is out of grid.   //
//////////////////////////////////////////////////////////

// setBlock() sets currBlock on the grid
bool Panel::setBlock() {
    if (currBlock->canSet(grid.get())) {
        setGrid();
        return true;
    }
    return false;
}

void Panel::dropStar() {
    blocks.emplace_back(make_unique<starBlock>());
    Block *theStar = blocks.back().get();
    while (theStar->canSet(grid.get())) {
        theStar->drop(grid.get());
        grid->getCell(theStar->getRow(), theStar->getCol()).setBlockPtr(theStar);
    }
}


// setGrid() changes the cells to let them point to the currBlock.
void Panel::setGrid() {
    vector<pair<int, int>> vec = currBlock->getCoord();
    for (int i = 0; i < 4; i++) {
        grid->getCell(vec[i].first, vec[i].second).setBlockPtr(currBlock);
    }
}

// unSetGrid() changes the cells pointing nullptr.
void Panel::unSetGrid() {
    vector<pair<int, int>> vec = currBlock->getCoord();
    for (int i = 0; i < 4; i++) {
        grid->getCell(vec[i].first, vec[i].second).setBlockPtr(nullptr);
    }
}




// canClear(int row) returns true if the row can be cleared, otherwise false.
bool Panel::canClear(int row) {
    for (int i = 0; i < 11; ++i) {
        if (!grid->getCell(row, i).isOccupied()) {
            return false;
        }
    }
    level4drop = 0;
    return true;
}

// clearRows(i) clears the rows and mutate clearedRows to the number of
//   cleared rows. It fixes the grid as well.
void Panel::clearRows(int &clearedRows) {
    int i = 17;
    while (i >= 0) {
        if(canClear(i)) {
            clearedRows ++;
            for (int j = 0; j < 11; j++) {
                grid->getCell(i, j).getBlock()->addElim();
            }
            grid->adjustGrid(i);
            i = 17;
        } else {
            --i;
        }
    }
}

int Panel::getBlockScore() {
    int total = 0;
    int size = blocks.size();
    for (int i = 0; i < size; ++i) {
        if (blocks[i]->getElim() == 1 && blocks[i]->getType() == '*') {
            total += pow((blocks[i]->getLevel() + 1), 2);
        } else if (blocks[i]->getElim() == 4) {
            total += pow((blocks[i]->getLevel() + 1), 2);
        }
    }
    return total;
}

void Panel::levelUp(int multiplier) {
    int newLevel = level->getLevel() + multiplier;
    currLevel = newLevel > 4 ? 4 : newLevel;
    level = generateLevel();
    notifyObservers();
}

void Panel::levelDown(int multiplier) {
    int newLevel = level->getLevel() - multiplier;
    currLevel = newLevel < 0 ? 0 : newLevel;
    level = generateLevel();
    notifyObservers();
}

void Panel::updateLevel(std::string file) {
    int currLevel = level->getLevel();
    if (currLevel == 3 || currLevel == 4) {
        fileForLevel34 = file;
        level = generateLevel();
    }
}

int Panel::changeCurrBlock(string type) {
    char blockType = type[0];
    unSetGrid();
    bool isHeavy = false;
    if (currLevel == 3 || currLevel == 4) {
        isHeavy = true;
    }
    // blocks.erase(blocks.end()-1);
    switch(blockType) {
        case 'I':
            blocks.emplace_back(make_unique<IBlock>(currLevel, isHeavy));
            break;
        case 'J':
            blocks.emplace_back(make_unique<JBlock>(currLevel, isHeavy));
            break;
        case 'L':
            blocks.emplace_back(make_unique<LBlock>(currLevel, isHeavy));
            break;
        case 'O':
            blocks.emplace_back(make_unique<OBlock>(currLevel, isHeavy));
            break;
	    case 'S':
            blocks.emplace_back(make_unique<SBlock>(currLevel, isHeavy));
            break;
	    case 'Z':
            blocks.emplace_back(make_unique<ZBlock>(currLevel, isHeavy));
            break;
	    case 'T':
            blocks.emplace_back(make_unique<TBlock>(currLevel, isHeavy));
            break;
	    default:
		    break;
    }
    currBlock = blocks.back().get();
    bool isSet = setBlock();
    notifyObservers();
    if (!isSet) {
        return GameOver;
    }
    return NotSwitchPlayer;
}

bool Panel::getSpecialAction() {
    return specialAction;
}

void Panel::unSetSpecialAction() {
    specialAction = false;
}

void Panel::blind() {
    for (int row = 5; row <= 14; ++row) {
        for (int col = 2; col <= 8; ++col) {
            getGridPtr()->getCell(row, col).setBlind();
        }
    }
    notifyObservers();
}

void Panel::unBlind() {
    for (int row = 0; row <= 17; ++row) {
        for (int col = 0; col <= 10; ++col) {
            getGridPtr()->getCell(row, col).unSetBlind();
        }
    }
}

void Panel::heavy(int gravity) {
    currBlock->setGravity(gravity);
}

std::unique_ptr<Level> Panel::generateLevel() {
    switch(currLevel) {
        case 0:
            return make_unique<Level0>(fileForLevel0);    
        case 1:
            return make_unique<Level1>(seed);
        case 2:
            return make_unique<Level2>(seed);
        case 3:
            return make_unique<Level3>(seed, fileForLevel34);
        case 4:
            return make_unique<Level4>(seed, fileForLevel34);
        default:
            return nullptr;
    }
}

void Panel::withdraw() {
    int size = blocks.size();
    cout << size << endl;
    Block *b = blocks[size-3].get();
    vector<pair<int, int>> vec = b->getCoord();
    for (int i = 0; i < 4; i++) {
        grid->getCell(vec[i].first, vec[i].second).setBlockPtr(nullptr);
    }
    notifyObservers();
}

void Panel::clearRow() {
    unSetGrid();
    grid->adjustGrid(17);
    setGrid();
    notifyObservers();
}
