#ifndef _LBLOCK_H_
#define _LBLOCK_H_

#include "block.h"

class LBlock : public Block {
    public:
        LBlock(int level, int gravity, int row = 3, int col = 0, int state = 0);
        std::vector<std::pair<int, int>> getCoord() override;
};

#endif
