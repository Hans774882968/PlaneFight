#pragma once
#include "framework.h"
#ifndef ScoreBoard_H
#define ScoreBoard_H

class GameState;

class ScoreBoard {
public:
    int score;//��ǰ����
    int passNum;//��ǰ���ڵڼ���
    int curOriginScore;//���뵱ǰ�ؿ�ʱ�ĳ�ʼ����
    int totBlood;//�Ѿ����������ٸ�Ѫ��
    bool bossPeriod;//�Ƿ��ڴ򱾹�boss

    ScoreBoard();
    void addScore(int num);
    int silverBulletGetScore(int num);//���ҷ��ɻ����мӵķ�
    bool canGenerateBlood();
    bool canFightBoss();
    int bossRequireScore();//�򱾹�boss��Ҫ�ڱ��ػ�õķ���
    int bossGiveScore();//��������boss��õķ����������boss�����޹�
    void nextPass();
};

#endif