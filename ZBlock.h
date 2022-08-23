#ifndef _ZBLOCK_H_
#define _ZBLOCK_H_

#include "block.h"

class ZBlock : public Block {
    public:
        ZBlock(int level, int gravity, int row = 3, int col = 0, int state = 0);
        std::vector<std::pair<int, int>> getCoord() override;
};

#endif
