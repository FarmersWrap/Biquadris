#ifndef _LEVEL3_H_
#define _LEVEL3_H_

#include <string>
#include <memory>
#include "level.h"

class Block;

class Level3: public Level {
    public:
        Level3(int seed, std::string file = "");
        ~Level3();
        int getLevel() override;
        std::unique_ptr<Block> generateBlock() override;
    private:
        int seed;
        std::vector<char> seq;
        bool isRandom;
        int index = 0;
};

#endif 
