#ifndef _TBLOCK_H_
#define _TBLOCK_H_

#include "block.h"

class TBlock : public Block {
    public:
        TBlock(int level, int gravity, int row = 3, int col = 0, int state = 0);
        std::vector<std::pair<int, int>> getCoord() override;

};

#endif
