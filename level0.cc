#include <iostream>
#include <fstream>
#include "level0.h"
#include "TBlock.h"
#include "OBlock.h"
#include "IBlock.h"
#include "ZBlock.h"
#include "SBlock.h"
#include "JBlock.h"
#include "LBlock.h"

using namespace std;

Level0::Level0(string file): Level{} {
    char type;
    ifstream sequence{file};
    while (sequence >> type) {
        seq.emplace_back(type);
    }
}

Level0::~Level0() {}

int Level0::getLevel() {
    return 0;
}

unique_ptr<Block> Level0::generateBlock() {
    int gravity = 0;
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
