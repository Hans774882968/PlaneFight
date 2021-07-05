#pragma once
#ifndef EnemyBullet_H
#define EnemyBullet_H

#include "framework.h"
#include "Bullet.h"

class GameState;

class EnemyBullet: public Bullet{
public:
    static HBITMAP img[2];
    static CImage cimg[2];//为了方便地获取像素而设置的CImage对象
    static COLORREF* pData[2];//像素数据
    EnemyBullet();
    EnemyBullet(int x, int y, int direc, int w, int h, int v, int typ, HDC hdc);//typ表示不同类型的敌人发射的子弹
    int direc2ImgIdx();
    void initImg();
    void blit(HDC mdc,HDC bufdc);
    COLORREF getPixel(int x, int y);
};

#endif