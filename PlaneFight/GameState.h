#pragma once
#ifndef GameState_H
#define GameState_H

#include "framework.h"
//#include <GdiPlus.h>//��ʱ�ò���
//#pragma comment(lib, "GdiPlus.lib")//��ʱ�ò���
#include "MyPlane.h"
#include "Enemy.h"
#include "ScoreBoard.h"
#include "MyBullet.h"
#include "EnemyBullet.h"
#include "Explosion.h"
#include "Blood.h"
#include "SkillCD.h"

class GameState{
public:
    CRect rect;//��¼���ڴ�С
    CImage bg;//����
    CImage loading;//loading.gif
    int curY;//�����ƶ�����
    HDC	hdc, mdc, bufdc;//hdc����Ҫ�ģ�mdc��bufdc�ǻ���
    MyPlane *me;
    std::vector<Enemy> enemies;
    ScoreBoard sb;
    std::vector<MyBullet> myBullets;
    std::vector<EnemyBullet> enemyBullets;
    std::vector<Explosion> explos;//��ըЧ��
    std::vector<Blood> bloods;//Ѫ���ȵ���
    SkillCD levelUpCD, protectCD, silverBulletCD;//����CD������
    
    GameState(HWND hWnd);
    void bgPrepare();//ÿ���޸�passNum�����
    bool isBossPeriod();
    void moveBg();
    void updateBg();
    void drawLoading();
};

#endif