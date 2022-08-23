#include <cstdlib>
#include "level2.h"
#include "TBlock.h"
#include "OBlock.h"
#include "IBlock.h"
#include "ZBlock.h"
#include "SBlock.h"
#include "JBlock.h"
#include "LBlock.h"

using namespace std;

Level2::Level2(int seed): Level{}, seed{seed} {}

Level2::~Level2() {}

int Level2::getLevel() {
    return 2;
}

unique_ptr<Block> Level2::generateBlock() {
    int gravity = 0;
    char types[7]= {'I','J','L','O','S','Z','T'};
    int i = rand() % 7;
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
}
