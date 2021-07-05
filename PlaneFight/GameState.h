#pragma once
#ifndef GameState_H
#define GameState_H

#include "framework.h"
//#include <GdiPlus.h>//暂时用不上
//#pragma comment(lib, "GdiPlus.lib")//暂时用不上
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
    CRect rect;//记录窗口大小
    CImage bg;//背景
    CImage loading;//loading.gif
    int curY;//背景移动变量
    HDC	hdc, mdc, bufdc;//hdc是主要的，mdc和bufdc是缓冲
    MyPlane *me;
    std::vector<Enemy> enemies;
    ScoreBoard sb;
    std::vector<MyBullet> myBullets;
    std::vector<EnemyBullet> enemyBullets;
    std::vector<Explosion> explos;//爆炸效果
    std::vector<Blood> bloods;//血包等道具
    SkillCD levelUpCD, protectCD, silverBulletCD;//技能CD管理器
    
    GameState(HWND hWnd);
    void bgPrepare();//每次修改passNum后调用
    bool isBossPeriod();
    void moveBg();
    void updateBg();
    void drawLoading();
};

#endif