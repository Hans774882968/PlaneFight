#pragma once
#ifndef Blood_H
#define Blood_H

#include "framework.h"
#include "FlyObject.h"

class GameState;

class Blood: public FlyObject{
public:
    static HBITMAP img;
    static CImage cimg;//Ϊ�˷���ػ�ȡ���ض����õ�CImage����
    static COLORREF* pData;//��������
    int typ;
    int direcX;
    int moveCount;
    Blood();
    Blood(int w, int h, HDC hdc);
    static void initImg(int totW, int totH);
    void blit(HDC mdc,HDC bufdc);
    COLORREF getPixel(int x, int y);
    bool move();//�����Ƿ���ʧ
};

#endif