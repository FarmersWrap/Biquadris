#ifndef _PANEL_H_
#define _PANEL_H_

#include <string>
#include <memory>
#include <vector>
#include "subject.h"

class Score;
class Level;
class Grid;
class Block;

class Panel : public Subject {
    public:
        Panel(int startlevel, int seed, std::string file, std::string file34, int hiScore);
        ~Panel();
        Score *getScorePtr();
        Level *getLevelPtr();
        Grid *getGridPtr();
        Block *getCurrBlockPtr();
        Block *getNextBlockPtr();
        int moveBlock(bool toLeft, int down, int multiplier);
        int rotateBlock(bool clockwise, int multiplier);
        int dropBlock();
        int changeCurrBlock(std::string type);
        void levelUp(int multiplier);
        void levelDown(int multiplier);
        void updateLevel(std::string file);
        void runSequence(std::string file);
        bool getSpecialAction();
        void unSetSpecialAction();
        void blind();
        void unBlind();
        void heavy(int gravity);
        // bonus
        void withdraw();
        void clearRow();
    private:
        int currLevel;
        int seed;
        std::string fileForLevel0;
        std::string fileForLevel34;
        int hiScore;

        std::vector<std::unique_ptr<Block>> blocks;
        std::unique_ptr<Score> score;
        std::unique_ptr<Level> level;
        std::unique_ptr<Grid> grid;
        Block *currBlock;
        Block *nextBlock;
        bool specialAction = false;
        int level4drop = 0; // only for Level 4

        std::unique_ptr<Level> generateLevel();
        bool setBlock();
        int getBlockScore();
        void setGrid();
        void unSetGrid();
        bool canClear(int row);
        void clearRows(int &clearedRows);
        void dropStar();
};

#endif
