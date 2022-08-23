#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "gameplay.h"
#include "panel.h"
#include "score.h"
#include "interpreter.h"
#include "view.h"

#include <ncurses.h>

using namespace std;

static const int GameOver = -1;
static const int NotSwitchPlayer = 0;
static const int SwitchPlayer = 1;
static const int GameRestart = 2;
static const int runSeq = 3;

GamePlay::GamePlay(bool textOnly, int seed, std::string file1, std::string file2, int startLevel, int hiScore, bool isRandom, bool isBasicGame):
textOnly{textOnly}, seed{seed}, file1{file1}, file2{file2}, startLevel{startLevel}, hiScore{hiScore}, isRandom{isRandom}, isBasicGame{isBasicGame} {
    string fileForLevel34 = "";
    player1 = make_unique<Panel>(startLevel, seed, file1, fileForLevel34, hiScore);
    player2 = make_unique<Panel>(startLevel, seed, file2, fileForLevel34, hiScore);
    player1Ptr = player1.get();
    player2Ptr = player2.get();
    currPlayer = player1Ptr;
    interpreter = make_unique<Interpreter>(isBasicGame);
    view = make_unique<View>(textOnly, player1Ptr, player2Ptr);
    player1->attach(view.get());
    player2->attach(view.get());
    cout << view.get();
}

GamePlay::~GamePlay() {}

void GamePlay::printSpecialCommands() {
    cout << "- blind" << endl;
    cout << "- heavy" << endl;
    cout << "- force x, where x is one of the 'I', 'J', 'L', 'O', 'S', 'Z', 'T'"  << endl;
    if (!isBasicGame) {
        cout << "- clearrow (bonus): clear opponent's last row without calculating scores."  << endl;
    }
}

string GamePlay::doKeyboard() {
    while (isKeyboard) {
        initscr();
        raw();
        keypad(stdscr, true);
        noecho();
        int ch = getch();
        switch (ch) {
            case KEY_RIGHT:
                refresh();
                endwin();
                return "right";
            case KEY_LEFT:
                refresh();
                endwin();
                return "left";
            case KEY_DOWN:
                refresh();
                endwin();
                return "down";
            case KEY_UP:
                refresh();
                endwin();
                return "clockwise";
            case 32:
                refresh();
                endwin();
                return "drop";
            case 61:
                refresh();
                endwin();
                return "levelup";
            case 45:
                refresh();
                endwin();
                return "leveldown";
            case 105:
                refresh();
                endwin();
                return "I";
            case 106:
                refresh();
                endwin();
                return "J";
            case 122:
                refresh();
                endwin();
                return "Z";
            case 108:
                refresh();
                endwin();
                return "L";
            case 111:
                refresh();
                endwin();
                return "O";
            case 116:
                refresh();
                endwin();
                return "T";
            case 115:
                refresh();
                endwin();
                return "S";
            case 98:
                refresh();
                endwin();
                return "blind";
            case 102:
                refresh();
                endwin();
                return "force";
            case 104:
                refresh();
                endwin();
                return "heavy";
            case 119:
                refresh();
                endwin();
                return "withdraw";
            case 99:
                refresh();
                endwin();
                return "clearrow";
            case 120:
                refresh();
                endwin();
                return "disablebonus";
            case 101:
                refresh();
                endwin();
                return "enablebonus";
            case KEY_BACKSPACE:
                refresh();
                endwin();
                isKeyboard = false;
                break;
            default:
                break;
        }
    }
    return "";
}

void GamePlay::scoreSettle() {
    int p1Score = player1->getScorePtr()->getScore();
    int p2Score = player2->getScorePtr()->getScore();
    if (p1Score > p2Score) {
        cout << "Player 1 won this round!" << endl;
    } else if (p1Score < p2Score) {
        cout << "Player 2 won this round!" << endl;
    } else if (currPlayer == player1Ptr) {
        cout << "Player 2 won this round!" << endl;
    } else {
        cout << "Player 1 won this round!" << endl;
    }
}

void GamePlay::start() {
    string cmd;
    string specialCmd;
    ifstream file;
    cout << "Do you want to use keyboard to play? Enter: Yes / No" << endl;
    string answer = "No";
    cin >> answer;
    if (answer.substr(0, 1) == "y" || answer.substr(0, 1) == "Y") {
        isKeyboard = true;
    } else {
        isKeyboard = false;
    }
    while (true) {
        if (isKeyboard) {
            cmd = doKeyboard();
        }
        if (!isKeyboard) {
            cin >> cmd;
        }
        if (cmd.substr(0, 2) == "en") {
        	isBasicGame = false;
        	cout << "Bonus Enabled: " << boolalpha << !isBasicGame << endl;
        	continue;
	    } else if (cmd.substr(0, 3) == "dis") {
	    	isBasicGame = true;
            cout << "Bonus Enabled: " << boolalpha << !isBasicGame << endl;
        	continue;
	    }
        Panel *otherPlayer = currPlayer == player1Ptr ? player2Ptr : player1Ptr;
        int rv = interpreter->interpret(cmd, currPlayer, isBasicGame);
        if (rv == SwitchPlayer) {
            if (currPlayer->getSpecialAction()) {
                cout << "Please enter the following special commands:" << endl;
                printSpecialCommands();
                if (isKeyboard) {
                    specialCmd = doKeyboard();
                } else {
                    cin >> specialCmd;
                }
                while (true) {
                    if (specialCmd.substr(0, 2) == "bl") {
                        otherPlayer->blind();
                        currPlayer->unSetSpecialAction();
                        break;
                    } else if (specialCmd.substr(0, 2) == "he") {
                        int heaviness = 2;
                        otherPlayer->heavy(heaviness);
                        currPlayer->unSetSpecialAction();
                        break;
                    } else if (specialCmd.substr(0, 2) == "fo") {
                        string type;
                        if (isKeyboard) {
                            type = doKeyboard();
                        } else {
                            cin >> type;
                        }
                        rv = otherPlayer->changeCurrBlock(type);
                        if (rv == GameOver) {
                            scoreSettle();
                            bool playAgain = restart();
                            if(!playAgain) {
                                return;
                            }
                        }
                        currPlayer->unSetSpecialAction();
                        break;
                    } else if (specialCmd == "clearrow") { // bonus
                        if (!isBasicGame) {
                            otherPlayer->clearRow();
                        	currPlayer->unSetSpecialAction();
                        	break;
                        } else {
                        	cout << "You cannot not do Bonus! Please enter the following special commands:" << endl;
                            printSpecialCommands();
                            cin >> specialCmd;
                        }
                    } else {
                        cout << "Invalid command! Please enter the following special commands:" << endl;
                        printSpecialCommands();
                        cin >> specialCmd;
                    }
                }
            }
            currPlayer = otherPlayer;
        } else if (rv == GameOver) {
            scoreSettle();
            bool playAgain = restart();
            if(!playAgain) {
                return;
            }
        } else if (rv == GameRestart) { 
            forceRestart();
        } else if (rv == runSeq) {
            runSequence();
        }
    }
}

void GamePlay::runSequence() {
    string cmd;
    string specialCmd;
    ifstream file;
    string seqfile;
    cin >> seqfile;
    ifstream ifs{seqfile};
    while (ifs >> cmd) {
        if (cmd.substr(0, 2) == "en") {
        	isBasicGame = false;
        	cout << "Bonus Enabled: " << boolalpha << !isBasicGame << endl;
        	continue;
	    } else if (cmd.substr(0, 3) == "dis") {
	    	isBasicGame = true;
        	cout << "Bonus Enabled: " << boolalpha << !isBasicGame << endl;
        	continue;
	    }
        Panel *otherPlayer = currPlayer == player1Ptr ? player2Ptr : player1Ptr;
        int rv = interpreter->interpret(cmd, currPlayer, isBasicGame);
        if (rv == SwitchPlayer) {
            if (currPlayer->getSpecialAction()) {
                cout << "Please enter the following special commands:" << endl;
                printSpecialCommands();
                cin >> specialCmd;
                while (true) {
                    if (specialCmd == "blind") {
                        otherPlayer->blind();
                        currPlayer->unSetSpecialAction();
                        break;
                    } else if (specialCmd == "heavy") {
                        int heaviness = 2;
                        otherPlayer->heavy(heaviness);
                        currPlayer->unSetSpecialAction();
                        break;
                    } else if (specialCmd == "force") {
                        string type;
                        cin >> type;
                        rv = otherPlayer->changeCurrBlock(type);
                        if (rv == GameOver) {
                            scoreSettle();
                            bool playAgain = restart();
                            if(!playAgain) {
                                return;
                            }
                        }
                        currPlayer->unSetSpecialAction();
                        break;
                    } else if (specialCmd == "clearrow") { // bonus
                        if (!isBasicGame) {
                            otherPlayer->clearRow();
                        	currPlayer->unSetSpecialAction();
                        	break;
                        } else {
                        	cout << "You cannot not do Bonus! Please enter the following special commands:" << endl;
                            printSpecialCommands();
                            cin >> specialCmd;
                        }
                    } else {
                        cout << "Invalid command! Please enter the following special commands:" << endl;
                        printSpecialCommands();
                        cin >> specialCmd;
                    }
                }
            }
            currPlayer = otherPlayer;
        } else if (rv == GameOver) {
            scoreSettle();
            bool playAgain = restart();
            if(!playAgain) {
                return;
            }
        } else if (rv == GameRestart) { 
            forceRestart();
        } else if (rv == runSeq) {
            runSequence();
        }
    }
}

bool GamePlay::forceRestart() {
    int level = 0;
    cout << "Which level do you want to start with?" << endl;
    while (!(cin >> level) || level < 0 || level > 4) {
        cout << "Please enter a number between 0 and 4, inclusively:" << endl;
        cin.clear();
        cin.ignore();
    }
    string fileForLevel34 = "";
    startLevel = level;
    player1 = make_unique<Panel>(startLevel, seed, file1, fileForLevel34, player1->getScorePtr()->getHiScore());
    player2 = make_unique<Panel>(startLevel, seed, file2, fileForLevel34, player2->getScorePtr()->getHiScore());
    player1Ptr = player1.get();
    player2Ptr = player2.get();
    currPlayer = player1Ptr;
    view->setPlayers(player1Ptr, player2Ptr);
    player1->attach(view.get());
    player2->attach(view.get());   
    cout << view.get();
    view->restart();
    cout << "Game Restarted! Have Fun!" << endl;
    return true;
}

bool GamePlay::restart() {
    cout << "Do you want to play again? Enter: Yes / No" << endl;
    string answer = "No"; // default is not play again 
    cin >> answer;
    int level = 0;
    if (answer.substr(0, 1) == "y" || answer.substr(0, 1) == "Y") {
        cout << "Which level do you want to start with?" << endl; 
        while (!(cin >> level) || level < 0 || level > 4) {
            cout << "Please enter a number between 0 and 4, inclusively:" << endl;
            cin.clear();
            cin.ignore();
        }
        string fileForLevel34 = "";
        startLevel = level;     
        player1 = make_unique<Panel>(startLevel, seed, file1, fileForLevel34, player1->getScorePtr()->getHiScore());
        player2 = make_unique<Panel>(startLevel, seed, file2, fileForLevel34, player2->getScorePtr()->getHiScore());
        player1Ptr = player1.get();
        player2Ptr = player2.get();
        currPlayer = player1Ptr;
        view->setPlayers(player1Ptr, player2Ptr);
        player1->attach(view.get());
        player2->attach(view.get());
        cout << view.get();
        view->restart();
        cout << "Game Restarted! Have Fun!" << endl;
        return true;
    } else {
        int p1Score = player1->getScorePtr()->getHiScore();
        int p2Score = player2->getScorePtr()->getHiScore();
        cout << "**********************************" << endl;
        if (p1Score > p2Score) {
            cout << "Player 1 is the King of Biquadris!" << endl;
        } else if (p1Score < p2Score) {
            cout << "Player 2 is the King of Biquadris!" << endl;
        } else {
            cout << "GG, same level players..." << endl;
        }
        cout << "**********************************" << endl;
        cout << "Have a good day! MOO!" << endl;
        return false;
    }
}
