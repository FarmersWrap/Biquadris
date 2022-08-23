#include "score.h"

Score::Score(int score, int hiScore, int rowScore) : score{score}, hiScore{hiScore}, rowScore{rowScore} {} 

int Score::getScore() {
    return score;
}

int Score::getHiScore() {
    return hiScore;
}

void Score::update(int rScore, int blockScore) {
    rowScore += rScore;
    score = rowScore + blockScore;
    hiScore = score > hiScore ? score : hiScore;
}
