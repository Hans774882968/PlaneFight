#pragma once
#ifndef BossBullet_H
#define BossBullet_H

#include "framework.h"
#include "Bullet.h"

class GameState;

class BossBullet: public Bullet{
public:
    static HBITMAP img;
    static CImage cimg;//Ϊ�˷���ػ�ȡ���ض����õ�CImage����
    static COLORREF* pData;//��������
    BossBullet();
    BossBullet(int x, int y, int w, int h, HDC hdc);
    void initImg(int totW, int totH, LPCWSTR path);
    void blit(HDC mdc, HDC bufdc);
    COLORREF getPixel(int x, int y);
};

#endif