#ifndef _VIEW_H_
#define _VIEW_H_

#include <memory>
#include "observer.h"
#include "window.h"

class Panel;

class View : public Observer {
    public:
        View(bool textOnly, Panel *p1, Panel *p2);
        Panel *getPlayer1();
        Panel *getPlayer2();
        void setPlayers(Panel *p1, Panel *p2);
        void notify(Subject &s);
        void restart();
    private:
        bool textOnly;
        Panel *player1;
        Panel *player2;
        std::unique_ptr<Xwindow> xw = nullptr;
        void setUpGraphics(); 
        void updateGraphics();
        void updateHeader(int col, int row, bool isPlayer1);
        void updateGrid(int startCol, int startRow, bool isPlayer1);
        void updateNext(int startCol, int startRow, bool isPlayer1);
	    void updatePlayer1(int col, int row);
	    void updatePlayer2(int col, int row);
    friend std::ostream &operator<<(std::ostream &out, View *v);
};

#endif
