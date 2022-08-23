#ifndef _OBLOCK_H_
#define _OBLOCK_H_
#include "block.h"

class OBlock : public Block {
    public:
        OBlock(int level, int gravity, int row = 3, int col = 0, int state = 0);
        std::vector<std::pair<int, int>> getCoord() override;
};

#endif
