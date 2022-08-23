#ifndef _STARBLOCK_H_
#define _STARBLOCK_H_

#include "block.h"

class starBlock : public Block {
    public:
        starBlock(int level = 4, bool isHeavy = false, int row = 0, int col = 5, int state = 0);
        std::vector<std::pair<int, int>> getCoord() override;
};

#endif
