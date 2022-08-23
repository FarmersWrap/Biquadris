#include <iostream>
#include <string>
#include <sstream>
#include "interpreter.h"
#include "panel.h"

using namespace std;

static const int GameOver = -1;
static const int NotSwitchPlayer = 0;
static const int SwitchPlayer = 1;
static const int forceRestart = 2;
static const int runSeq = 3;

Interpreter::Interpreter(bool isBasicGame) {
    this->isBasicGame = isBasicGame;
}

int Interpreter::interpret(string cmd, Panel *currPlayer, bool isBasicGame) {
    string file;
    string realCmd;
    int multiplier;
    istringstream iss{cmd};
    if (!(iss >> multiplier)) {
        multiplier = 1;
        iss.clear();
    }
    iss >> realCmd;
    cout << "Your Command is: " << realCmd << endl;
    cout << "and you want to repeat " << multiplier << " time(s)" << endl;
    if (realCmd.substr(0, 3) == "lef" || realCmd == "^[[D") {
        return currPlayer->moveBlock(true, 0, multiplier);
    } else if (realCmd.substr(0, 2) == "ri" || realCmd == "^[[C") {  
        return currPlayer->moveBlock(false, 0, multiplier);
    } else if (realCmd.substr(0, 2) == "do" || realCmd == "^[[B") {
        return currPlayer->moveBlock(0, multiplier, 0);
    } else if (realCmd.substr(0, 2) == "cl") { 
        return currPlayer->rotateBlock(true, multiplier);
    } else if (realCmd.substr(0, 2) == "co") {
        return currPlayer->rotateBlock(false, multiplier);
    } else if (realCmd.substr(0, 2) == "dr") {
        for (int i = multiplier; i > 1; --i) {
            currPlayer->dropBlock();
        }
        return currPlayer->dropBlock();
    } else if (realCmd.substr(0, 6) == "levelu") {
        currPlayer->levelUp(multiplier);
        return NotSwitchPlayer;
    } else if (realCmd.substr(0, 6) == "leveld") {
        currPlayer->levelDown(multiplier);
        return NotSwitchPlayer;
    } else if (realCmd.substr(0, 2) == "no") {
        cin >> file;
        currPlayer->updateLevel(file);
        return NotSwitchPlayer;
    } else if (realCmd.substr(0, 2) == "ra") {
        currPlayer->updateLevel("");
        return NotSwitchPlayer;
    } else if (realCmd.substr(0, 2) == "se") {
        return runSeq;
    } else if (realCmd == "I" || realCmd == "J" || realCmd == "L" || realCmd == "O" ||
               realCmd == "S" || realCmd == "Z" || realCmd == "T") {
        return currPlayer->changeCurrBlock(realCmd);
    } else if (realCmd.substr(0, 2) == "re") {
        return forceRestart;
    } else if (realCmd.substr(0, 2) == "en") {
        isBasicGame = false;
        return NotSwitchPlayer;
    } else if (realCmd.substr(0, 2) == "un") {
        isBasicGame = true;
        return NotSwitchPlayer;
    } else if (realCmd == "withdraw") { // bonus
        if (!isBasicGame) {
            currPlayer->withdraw();
            return NotSwitchPlayer;
        }
    }
    cout << "Command is not valid! Please Re-enter:" << endl;
    return NotSwitchPlayer;
}
