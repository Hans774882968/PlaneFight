#pragma once
#ifndef MyBullet_H
#define MyBullet_H

#include "framework.h"
#include "Bullet.h"

class GameState;

class MyBullet: public Bullet{
public:
    static HBITMAP img[2];
    static CImage cimg[2];//Ϊ�˷���ػ�ȡ���ض����õ�CImage����
    static COLORREF* pData[2];//��������
    bool isLevelUp;
    MyBullet();
    MyBullet(int x, int y, bool isLevelUp, HDC hdc);
    void initImg();
    void blit(HDC mdc,HDC bufdc);
    COLORREF getPixel(int x, int y);
    int getAttack();
};

#endif