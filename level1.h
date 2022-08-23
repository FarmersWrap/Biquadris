#ifndef _LEVEL1_H_
#define _LEVEL1_H_

#include <string>
#include <memory>
#include "level.h"

class Block;

class Level1: public Level {
    public:
        Level1(int seed);
        ~Level1();
        int getLevel() override;
        std::unique_ptr<Block> generateBlock() override;
    private:
        int seed;
};

#endif 
