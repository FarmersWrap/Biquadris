#include "OBlock.h"

using namespace std;

OBlock::OBlock(int level, int gravity, int row, int col, int state):
Block{level, gravity, row, col, state} {
    type = 'O';
}

vector<pair<int, int>> OBlock::getCoord() {
    vector<pair<int, int>> vec = initialPairs();
    vec[1].second += 1;
    vec[2].first -= 1;
    vec[2].second += 1;
    vec[3].first -= 1;
    return vec;
}
