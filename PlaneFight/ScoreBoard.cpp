#include "ScoreBoard.h"
#include "GameState.h"

extern GameState* gs;

ScoreBoard::ScoreBoard() : score(0), curOriginScore(0) {
    totBlood = 0;
    passNum = 1;//dbg
    bossPeriod = false;
}

void ScoreBoard::addScore(int num) {
    score += num;
}

//���outBound()ֻ�Ǳ�֤����Ӧ�����ٵĸ��ӽ�����������ֻ�ӿ�������ĵ��ˡ�
int ScoreBoard::silverBulletGetScore(int num) {
    int s = 0;
    for (auto enemy : gs->enemies) {
        if (!enemy.outBound()) {
            s += num;
        }
    }
    return s;
}

bool ScoreBoard::canGenerateBlood() {
    if (gs->bloods.empty() && score - curOriginScore >= bossRequireScore() * (totBlood + 1) / 3) {
        ++totBlood;
        return true;
    }
    return false;
}

bool ScoreBoard::canFightBoss() {
    return score - curOriginScore >= bossRequireScore();
}

int ScoreBoard::bossRequireScore() {
    return 2500 + 500 * (passNum - 1);
}

int ScoreBoard::bossGiveScore() {
    return 2500 + 450 * (passNum - 1) + 1500 * (gs->me->life - 1) + 150 * gs->me->blood;
}

void ScoreBoard::nextPass() {
    if ((++passNum) > 7) passNum = 1;//��7�غ�������ת����1��
    curOriginScore = score;
    totBlood = 0;
    bossPeriod = false;
}