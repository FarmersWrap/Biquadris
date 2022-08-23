#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_

#include <string>

class Panel;

class Interpreter {
    public:
        Interpreter(bool isBasicGame);
        int interpret(std::string cmd, Panel *currPlayer, bool isBasicGame);
        // bool doSpecialAction(std::string cmd, Panel *aggressor, Panel *victim);
    private:
        bool isBasicGame;
};

#endif
