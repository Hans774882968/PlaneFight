#pragma once
#ifndef Bullet_H
#define Bullet_H

#include "framework.h"
#include "FlyObject.h"

class GameState;

class Bullet: public FlyObject{
public:
    int index, totIndex;
    Bullet();
    Bullet(int x, int y, int direc, int w, int h, int v, int initIndex, int totIndex, HDC hdc);//initIndex表示不同类型的敌人发射的子弹
    virtual void initImg(int totW, int totH, LPCWSTR path);//除敌机子弹外
    virtual void initImg();//敌机子弹
    virtual COLORREF getPixel(int x, int y) = 0;
    void move();
    void anime();
};

#endif