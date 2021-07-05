#pragma once
#include "framework.h"
#ifndef ScoreBoard_H
#define ScoreBoard_H

class GameState;

class ScoreBoard {
public:
    int score;//当前分数
    int passNum;//当前处于第几关
    int curOriginScore;//进入当前关卡时的初始分数
    int totBlood;//已经产生过多少个血包
    bool bossPeriod;//是否在打本关boss

    ScoreBoard();
    void addScore(int num);
    int silverBulletGetScore(int num);//求我方飞机大招加的分
    bool canGenerateBlood();
    bool canFightBoss();
    int bossRequireScore();//打本关boss需要在本关获得的分数
    int bossGiveScore();//打死本关boss获得的分数，与具体boss对象无关
    void nextPass();
};

#endif