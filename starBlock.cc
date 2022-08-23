#include "starBlock.h"

using namespace std;

starBlock::starBlock(int level, bool isHeavy, int row, int col, int state) :
Block{level, isHeavy, row, col, state} {
    type = '*';
}

vector<pair<int, int>> starBlock::getCoord() {
    vector<pair<int, int>> vec = initialPairs();
    return vec;
}
