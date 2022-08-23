#include "grid.h"

using namespace std;

const int gridWidth = 11;
const int gridHeight = 18;

Grid::Grid() {
    for (int row = 0; row < gridHeight; ++row) {
		vector<Cell> vecRow;
		for (int col = 0; col < gridWidth; ++col) {
			vecRow.emplace_back(Cell(row, col));
		}
		grid.emplace_back(vecRow);
	}
}

Cell &Grid::getCell(int row, int col) {
    return grid[row][col];
}

void Grid::adjustGrid(int i) {
	grid.erase(grid.begin() + i);
    vector<Cell> vec;
    for (int i = 0; i < gridWidth; ++i) {
        vec.emplace_back(Cell(0, i));
    }
    grid.insert(grid.begin(), vec);
    for (int i = 0; i < gridHeight; ++i) {
		for (int j = 0; j < gridWidth; ++j) {
			getCell(i, j).setRow(i);
			getCell(i, j).setCol(j);
		}
	}
}
