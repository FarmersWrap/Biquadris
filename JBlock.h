#ifndef _JBLOCK_H_
#define _JBLOCK_H_

#include "block.h"

class JBlock : public Block {
    public:
        JBlock(int level, int gravity, int row = 3, int col = 0, int state = 0);
        std::vector<std::pair<int, int>> getCoord() override;
};

#endif
