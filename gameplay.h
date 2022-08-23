#ifndef _GAMEPLAY_H_
#define _GAMEPLAY_H_

#include <string>
#include <memory>

class Panel;
class Interpreter;
class View;

class GamePlay {
    public:
        // ====== ctors ======
        GamePlay(bool textOnly, int seed, std::string file1, std::string file2, int startLevel, int hiScore, bool isRandom, bool isBasicGame);
        // ====== dtor ======
        ~GamePlay();
        // ====== methods ======
        void start();
        bool restart();
        bool forceRestart();
        void runSequence();
    private:
        bool textOnly;
        int seed;
        std::string file1;
        std::string file2;
        int startLevel;
        int hiScore;
        bool isRandom;
        bool isBasicGame;
        bool isKeyboard = false;
        
        std::unique_ptr<Panel> player1;
        std::unique_ptr<Panel> player2;
        std::unique_ptr<Interpreter> interpreter;
        std::unique_ptr<View> view;
        Panel *player1Ptr;
        Panel *player2Ptr;
        Panel *currPlayer;

        void printSpecialCommands();
        void scoreSettle();
        std::string doKeyboard();
};

#endif
