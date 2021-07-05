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
    Bullet(int x, int y, int direc, int w, int h, int v, int initIndex, int totIndex, HDC hdc);//initIndex��ʾ��ͬ���͵ĵ��˷�����ӵ�
    virtual void initImg(int totW, int totH, LPCWSTR path);//���л��ӵ���
    virtual void initImg();//�л��ӵ�
    virtual COLORREF getPixel(int x, int y) = 0;
    void move();
    void anime();
};

#endif