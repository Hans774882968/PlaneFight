#pragma once
#ifndef MyBullet_H
#define MyBullet_H

#include "framework.h"
#include "Bullet.h"

class GameState;

class MyBullet: public Bullet{
public:
    static HBITMAP img[2];
    static CImage cimg[2];//为了方便地获取像素而设置的CImage对象
    static COLORREF* pData[2];//像素数据
    bool isLevelUp;
    MyBullet();
    MyBullet(int x, int y, bool isLevelUp, HDC hdc);
    void initImg();
    void blit(HDC mdc,HDC bufdc);
    COLORREF getPixel(int x, int y);
    int getAttack();
};

#endif