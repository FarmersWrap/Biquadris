#ifndef _LEVEL4_H_
#define _LEVEL4_H_

#include <string>
#include <memory>
#include "level.h"

class Block;

class Level4: public Level {
    public:
        Level4(int seed, std::string file = "");
        ~Level4();
        int getLevel() override;
        std::unique_ptr<Block> generateBlock() override;
    private:
        int seed;
        std::vector<char> seq;
        bool isRandom;
        int index = 0;
};

#endif
