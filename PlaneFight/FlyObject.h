#pragma once
#ifndef FlyObject_H
#define FlyObject_H

#include "framework.h"

class GameState;

class FlyObject{
public:
    int x, y, v, direc;
    HDC hdc;//�������������ڵ�hdc
    int w, h;//���£��޸����زĵĴ�С���Ӵ˲���Ҫ�������űȡ���һ�Ķ���Ϊ�ˡ����ؼ���ײ��⡱��ʵ��
    
    FlyObject();
    FlyObject(int x, int y, HDC hdc);
    FlyObject(int x, int y, int w, int h, HDC hdc);
    FlyObject(int x, int y, int w, int h, int v, HDC hdc);
    FlyObject(int x, int y, int w, int h, int v, int direc, HDC hdc);
    bool outBound();
    virtual COLORREF getPixel(int x, int y) = 0;//����enemy.typ��me->index�ȣ���ȡ��������
    bool collision(FlyObject *other);
};

#endif