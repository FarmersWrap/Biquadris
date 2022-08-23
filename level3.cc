#include <cstdlib>
#include <fstream>
#include "level3.h"
#include "TBlock.h"
#include "OBlock.h"
#include "IBlock.h"
#include "ZBlock.h"
#include "SBlock.h"
#include "JBlock.h"
#include "LBlock.h"

using namespace std;

Level3::Level3(int seed, string file): Level{}, seed{seed} {
    if (file == "") {
        isRandom = true;
    } else {
        char type;
        ifstream sequence{file};
        while (sequence >> type) {
            seq.emplace_back(type);
        }
        isRandom = false;
    }
}

Level3::~Level3() {}

int Level3::getLevel() {
    return 3;
}

unique_ptr<Block> Level3::generateBlock() {
    int gravity = 1;
    if (isRandom) {
        char types[9] = {'S','S','Z','Z','I','J','L','O','T'};
        int i = rand() % 9;
        char type = types[i];
        switch(type) {
            case 'I':
                return make_unique<IBlock>(getLevel(), gravity);
            case 'J':
                return make_unique<JBlock>(getLevel(), gravity);
            case 'L':
                return make_unique<LBlock>(getLevel(), gravity);
            case 'O':
                return make_unique<OBlock>(getLevel(), gravity);
            case 'S':
                return make_unique<SBlock>(getLevel(), gravity);
            case 'Z':
                return make_unique<ZBlock>(getLevel(), gravity);
            case 'T':
                return make_unique<TBlock>(getLevel(), gravity);
            default:
                return nullptr;
        }
    } else {
        int size = seq.size();
        if (index == size) {
            index = 0;
        }
        char type = seq[index];
        index += 1;
        switch(type) {
            case 'I':
                return make_unique<IBlock>(getLevel(), gravity);
            case 'J':
                return make_unique<JBlock>(getLevel(), gravity);
            case 'L':
                return make_unique<LBlock>(getLevel(), gravity);
            case 'O':
                return make_unique<OBlock>(getLevel(), gravity);
            case 'S':
                return make_unique<SBlock>(getLevel(), gravity);
            case 'Z':
                return make_unique<ZBlock>(getLevel(), gravity);
            case 'T':
                return make_unique<TBlock>(getLevel(), gravity);
            default:
                return nullptr;
        }
    }
}

