#ifndef _SCORE_H_
#define _SCORE_H_

class Score {
    public:
        Score(int score, int hiScore, int rowScore = 0);
        int getScore();
        int getHiScore();
        void update(int rowScore, int blockScore);
    private:
        int score;
        int hiScore;
        int rowScore;
};

#endif
