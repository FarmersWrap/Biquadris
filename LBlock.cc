#include "LBlock.h"

using namespace std;

LBlock::LBlock(int level, int gravity, int row, int col, int state):
Block{level, gravity, row, col, state} {
    type = 'L';
}

vector<pair<int, int>> LBlock::getCoord() {
    vector<pair<int, int>> vec = initialPairs();
    if (state % 4 == 0) {
        vec[0].first -= 1;
        vec[0].second += 2;
        vec[1].second += 2;
        vec[2].second += 1;
    } else if (state % 4 == 1) {
        vec[0].second += 1;
        vec[2].first -= 1;
        vec[3].first -= 2;
    } else if (state % 4 == 2) {
        vec[1].first -= 1;
        vec[2].first -= 1;
        vec[2].second += 1;
        vec[3].first -= 1;
        vec[3].second += 2;
    } else if (state % 4 == 3) {
        vec[0].first -= 2;
        vec[1].first -= 2;
        vec[1].second += 1;
        vec[2].first -= 1;
        vec[2].second += 1;
        vec[3].second += 1;
    }
    return vec;
}
