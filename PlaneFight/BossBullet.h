#pragma once
#ifndef BossBullet_H
#define BossBullet_H

#include "framework.h"
#include "Bullet.h"

class GameState;

class BossBullet: public Bullet{
public:
    static HBITMAP img;
    static CImage cimg;//为了方便地获取像素而设置的CImage对象
    static COLORREF* pData;//像素数据
    BossBullet();
    BossBullet(int x, int y, int w, int h, HDC hdc);
    void initImg(int totW, int totH, LPCWSTR path);
    void blit(HDC mdc, HDC bufdc);
    COLORREF getPixel(int x, int y);
};

#endif