#include <iostream>
#include <iomanip>
#include "view.h"
#include "panel.h"
#include "grid.h"
#include "score.h"
#include "cell.h"
#include "block.h"
#include "level.h"

using namespace std;

View::View(bool textOnly, Panel *p1, Panel *p2) : 
Observer{}, textOnly{textOnly}, player1{p1}, player2{p2} {
	if (!textOnly) {
		setUpGraphics();
	}
}

int colorConversion(char type) {
	switch(type) {
		case 'I':
			return Xwindow::Red;
		case 'J':
			return Xwindow::Green;
		case 'L':
			return Xwindow::Blue;
		case 'O':
			return Xwindow::DarkGreen;
		case 'S':
			return Xwindow::Magenta;
		case 'Z':
			return Xwindow::Orange;
		case '*':
			return Xwindow::Brown;
		case 'T':
			return Xwindow::Yellow;
		default:
			return Xwindow::White;
	}
    return Xwindow::White;
}

void View::setUpGraphics() {
	if (!textOnly) {
		xw = make_unique<Xwindow>(950, 800);
		xw->fillRectangle(0, 0, 950, 800, Xwindow::Black);
		updateGraphics();
	}
}

void View::restart() {
	if (!textOnly) {
		xw->fillRectangle(0, 0, 950, 800, Xwindow::Black);
		updateGraphics();
	}
}

void View::updatePlayer1(int col, int row) {
	updateHeader(col, row, true);
	updateGrid(col, row, true);
	updateNext(col, row, true);
}

void View::updatePlayer2(int col, int row) {
	updateHeader(col, row, false);
	updateGrid(col, row, false);
	updateNext(col, row, false);
}

void View::updateGraphics() {
	updatePlayer1(20, 0);
	updatePlayer2(475, 0);
	xw->drawString(50, 30, "Biquadris  Made by Zhenchao, Zhenglin, Ying", Xwindow::White);
}

void View::updateHeader(int col, int row, bool isPlayer1) {
	
	xw->fillRectangle(col, 45, 475, 40, Xwindow::Black);

	xw->drawString(col + 70, row + 70, "Score:", Xwindow::White);
	xw->drawString(col + 168, row + 70, "level:", Xwindow::White);
	xw->drawString(col + 300, row + 70, "HiScore:", Xwindow::White);
	int score = 0;
	int level = 0;
	int HiScore = 0;
	if (isPlayer1) {
		score = getPlayer1()->getScorePtr()->getScore();
		level = getPlayer1()->getLevelPtr()->getLevel();
		HiScore = getPlayer1()->getScorePtr()->getHiScore();
	} else {
		score = getPlayer2()->getScorePtr()->getScore();
		level = getPlayer2()->getLevelPtr()->getLevel();
		HiScore = getPlayer2()->getScorePtr()->getHiScore();
	}
	xw->drawString(col + 128, row + 70, to_string(score), Xwindow::White);
	xw->drawString(col + 228, row + 70, to_string(level), Xwindow::White);
	xw->drawString(col + 370, row + 70, to_string(HiScore), Xwindow::White);

}

void View::updateGrid(int startCol, int startRow, bool isPlayer1) {
	for (int row = 0; row < gridHeight; ++row) {
		for (int col = 0; col < gridWidth; ++col) {
			bool occupied = 0;
			if (isPlayer1) {
				occupied = getPlayer1()->getGridPtr()->getCell(row, col).isOccupied();
			} else {
				occupied = getPlayer2()->getGridPtr()->getCell(row, col).isOccupied();
			}
			if (occupied) {
				int printed = 0;
				if (isPlayer1) {
					printed = colorConversion(getPlayer1()->getGridPtr()->getCell(row, col).getBlockType());
				} else {
					printed = colorConversion(getPlayer2()->getGridPtr()->getCell(row, col).getBlockType());
				}
				xw->fillRectangle(startCol + 60 + col * 32, startRow + 90 + row * 32, 30, 30, printed);
			} else {
				xw->fillRectangle(startCol + 60 + col * 32, startRow + 90 + row * 32, 30, 30, Xwindow::White);
			}
			if (isPlayer1 && getPlayer1()->getGridPtr()->getCell(row, col).getIsBlind()) {
				xw->fillRectangle(startCol + 60 + col * 32, startRow + 90 + row * 32, 30, 30, Xwindow::Black);
			} else if (!isPlayer1 && getPlayer2()->getGridPtr()->getCell(row, col).getIsBlind()) {
				xw->fillRectangle(startCol + 60 + col * 32, startRow + 90 + row * 32, 30, 30, Xwindow::Black);
			}
		}
	}
}

void View::updateNext(int col, int row, bool isPlayer1) {
	xw->fillRectangle(col, 670, 475, 150, Xwindow::Black);
    xw->drawString(col + 95, row + 700, "Next:", Xwindow::White);
	vector<pair<int, int>> vec;
	if (isPlayer1) {
		vec = player1->getNextBlockPtr()->getCoord();
	} else {
		vec = player2->getNextBlockPtr()->getCoord();
	}

	int baseCol = 260;
	int baseRow = 629;
	for (int i = 0; i < 4; i++) {
		int printed = 0;
		if (isPlayer1) {
			printed = colorConversion(player1->getNextBlockPtr()->getType());
		} else {
			printed = colorConversion(player2->getNextBlockPtr()->getType());
		}
		xw->fillRectangle(col + vec[i].second * 32 + baseCol, 
		row + vec[i].first * 32 + baseRow, 30, 30, printed);
	}
}

Panel *View::getPlayer1() {
	return player1;
}
Panel *View::getPlayer2() {
	return player2;
}

void View::setPlayers(Panel *p1, Panel *p2) {
	player1 = p1;	
	player2 = p2;
}

void View::notify(Subject &s) {
	if(!textOnly) {
		updateGraphics();
    }
	cout << this;
}

static ostream & NextBlockLine1(ostream &out, char type) {
    switch(type) {
		case 'I':
			out << "          ";
			break;
		case 'J':
			out << "J         ";
			break;
		case 'L':
			out << "  L       ";
			break;
		case 'O':
			out << "OO        ";
			break;
		case 'S':
			out << " SS       ";
			break;
		case 'Z':
			out << "ZZ        ";
			break;
		case 'T':
			out << "TTT       ";
			break;
		default:
			break;
	}
    return out;
}

static ostream & NextBlockLine2(ostream &out, char type) {
    switch(type) {
		case 'I':
			out << "IIII       ";
			break;
		case 'J':
			out << "JJJ        ";
			break;
		case 'L':
			out << "LLL        ";
			break;
		case 'O':
			out << "OO         ";
			break;
		case 'S':
			out << "SS         ";
			break;
		case 'Z':
			out << " ZZ        ";
			break;
		case 'T':
			out << " T         ";
			break;
		default:
			break;
	}
    return out;
}

static ostream &printNext(int lineNum, ostream &out, char type1, char type2) {
    if (lineNum == 1) {
        NextBlockLine1(out, type1);
        out << '\t' << '\t';
        NextBlockLine1(out, type2);
    } else if (lineNum == 2) {
        NextBlockLine2(out, type1);
        out << '\t' << '\t';
        NextBlockLine2(out, type2);
    }
    return out;
}

ostream &operator<<(ostream &out, View *v) {
	// HiScore Line
	out << "HiScore:" << "  " << v->getPlayer1()->getScorePtr()->getHiScore();
	out << '\t' << '\t';
	out << "HiScore:" << "  " << v->getPlayer2()->getScorePtr()->getHiScore();
	out << endl;
	// Score Line
	out << "Score:" << "    " << v->getPlayer1()->getScorePtr()->getScore();
	out << '\t' << '\t';
	out << "Score:" << "    " << v->getPlayer2()->getScorePtr()->getScore();
	out << endl;
	// Level Line
	out << "Level:" << "    " << v->getPlayer1()->getLevelPtr()->getLevel();
	out << '\t' << '\t';
	out << "Level:" << "    " << v->getPlayer2()->getLevelPtr()->getLevel();
	out << endl;
	// Line Break
	out << "-----------" << '\t' << '\t' << "-----------" << endl;
	for (int row = 0; row < gridHeight; ++row) {
		for (int col = 0; col < gridWidth; ++col) {
			bool occupied = v->getPlayer1()->getGridPtr()->getCell(row, col).isOccupied();
			char printed = ' ';
			if (occupied) {
				printed = v->getPlayer1()->getGridPtr()->getCell(row, col).getBlockType();
			}
			bool blind = v->getPlayer1()->getGridPtr()->getCell(row, col).getIsBlind();
			if (blind) {
				printed = '?';
			}
			out << printed; 
		}
		out << '\t' << '\t';
		for (int col = 0; col < gridWidth; ++col) {
			bool occupied = v->getPlayer2()->getGridPtr()->getCell(row, col).isOccupied();
			char printed = ' ';
			if (occupied) {
				printed = v->getPlayer2()->getGridPtr()->getCell(row, col).getBlockType();
			}
			bool blind = v->getPlayer2()->getGridPtr()->getCell(row, col).getIsBlind();
			if (blind) {
				printed = '?';
			}
			out << printed; 
		}
		out << endl;
	}
	out << "-----------" << '\t' << '\t' << "-----------" << endl;
	out << "Next:      " << '\t' << '\t' << "Next:      " << endl;
    printNext(1, out, v->getPlayer1()->getNextBlockPtr()->getType(), v->getPlayer2()->getNextBlockPtr()->getType());
    out << endl;
    printNext(2, out, v->getPlayer1()->getNextBlockPtr()->getType(), v->getPlayer2()->getNextBlockPtr()->getType());
    out << endl;
    return out;
}
