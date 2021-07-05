#pragma once
#ifndef FlyObject_H
#define FlyObject_H

#include "framework.h"

class GameState;

class FlyObject{
public:
    int x, y, v, direc;
    HDC hdc;//对象所隶属窗口的hdc
    int w, h;//更新：修改了素材的大小，从此不需要设置缩放比。这一改动是为了“像素级碰撞检测”的实现
    
    FlyObject();
    FlyObject(int x, int y, HDC hdc);
    FlyObject(int x, int y, int w, int h, HDC hdc);
    FlyObject(int x, int y, int w, int h, int v, HDC hdc);
    FlyObject(int x, int y, int w, int h, int v, int direc, HDC hdc);
    bool outBound();
    virtual COLORREF getPixel(int x, int y) = 0;//根据enemy.typ和me->index等，获取像素数据
    bool collision(FlyObject *other);
};

#endif