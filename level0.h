#ifndef _LEVEL0_H_
#define _LEVEL0_H_

#include <string>
#include <memory>
#include "level.h"

class Block;

class Level0: public Level {
    public:
        Level0(std::string file);
        ~Level0();
        int getLevel() override;
        std::unique_ptr<Block> generateBlock() override;
    private:
        std::vector<char> seq;
        int index = 0;
};

#endif 
