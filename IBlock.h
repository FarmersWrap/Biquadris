#ifndef _IBLOCK_H_
#define _IBLOCK_H_

#include "block.h"

class IBlock : public Block {
    public:
        IBlock(int level, int gravity, int row = 3, int col = 0, int state = 0);
        std::vector<std::pair<int, int>> getCoord() override;
};

#endif

