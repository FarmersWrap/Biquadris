#include "IBlock.h"

using namespace std;

IBlock::IBlock(int level, int gravity, int row, int col, int state) :
Block{level, gravity, row, col, state} {
    type = 'I';
}

vector<pair<int, int>> IBlock::getCoord() {
    vector<pair<int, int>> vec = initialPairs();
    if (state % 2 == 0) {
        vec[1].second += 1;
        vec[2].second += 2;
        vec[3].second += 3;
    } else {
        vec[1].first -= 1;
        vec[2].first -= 2;
        vec[3].first -= 3;
    }
    return vec;
}
