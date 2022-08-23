#ifndef _SBLOCK_H_
#define _SBLOCK_H_

#include "block.h"

class SBlock : public Block {
    public:
        SBlock(int level, int gravity, int row = 3, int col = 0, int state = 0);
        std::vector<std::pair<int, int>> getCoord() override;
};

#endif
