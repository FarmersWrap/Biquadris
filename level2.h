#ifndef _LEVEL2_H_
#define _LEVEL2_H_

#include <string>
#include <memory>
#include "level.h"

class Block;

class Level2: public Level {
    public:
        Level2(int seed);
        ~Level2();
        int getLevel() override;
        std::unique_ptr<Block> generateBlock() override;
    private:
        int seed;
};

#endif 
