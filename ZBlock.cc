#include "ZBlock.h"

using namespace std;

ZBlock::ZBlock(int level, int gravity, int row, int col, int state):
Block{level, gravity, row, col, state} {
    type = 'Z';
}

vector<pair<int, int>> ZBlock::getCoord() {
    vector<pair<int, int>> vec = initialPairs();
    if (state % 2 == 0) {
        vec[0].first -= 1;
        vec[1].first -= 1;
        vec[1].second += 1;
        vec[2].second += 1;
        vec[3].second += 2;
    } else {
        vec[0].first -= 2;
        vec[0].second += 1;
        vec[1].first -= 1;
        vec[1].second += 1;
        vec[2].first -= 1;
    }
    return vec;
}
