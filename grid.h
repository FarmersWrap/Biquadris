#ifndef _GRID_H_
#define _GRID_H_

#include <vector>
#include "cell.h"

extern const int gridWidth;
extern const int gridHeight;

class Grid {
    public:
        Grid();
        Cell &getCell(int row, int col);
        void adjustGrid(int i);
    private:
        std::vector<std::vector<Cell>> grid;
};

#endif 





