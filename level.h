#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <vector>
#include <memory>
#include <string>

class Block;

class Level {
    public:
        Level();
        virtual ~Level();
        virtual int getLevel() = 0;
        virtual std::unique_ptr<Block> generateBlock() = 0;
};

#endif
