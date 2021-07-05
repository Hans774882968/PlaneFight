#pragma once
#ifndef Explosion_H
#define Explosion_H

#include "framework.h"
#include "FlyObject.h"

class GameState;

class Explosion: public FlyObject{
public:
    static HBITMAP img;
    int index, totIndex;
    Explosion();
    Explosion(int x, int y, HDC hdc);
    static void initImg();
    void blit(HDC mdc, HDC bufdc);
    COLORREF getPixel(int x, int y);
    bool anime();//返回：是否应消失
};

#endif