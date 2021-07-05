#pragma once
#ifndef Blood_H
#define Blood_H

#include "framework.h"
#include "FlyObject.h"

class GameState;

class Blood: public FlyObject{
public:
    static HBITMAP img;
    static CImage cimg;//为了方便地获取像素而设置的CImage对象
    static COLORREF* pData;//像素数据
    int typ;
    int direcX;
    int moveCount;
    Blood();
    Blood(int w, int h, HDC hdc);
    static void initImg(int totW, int totH);
    void blit(HDC mdc,HDC bufdc);
    COLORREF getPixel(int x, int y);
    bool move();//返回是否消失
};

#endif