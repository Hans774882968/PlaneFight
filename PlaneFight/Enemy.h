#pragma once
#ifndef Enemy_H
#define Enemy_H

#include "framework.h"
#include "FlyObject.h"

class GameState;

class Enemy: public FlyObject{
public:
    static HBITMAP img[2];
    static CImage cimg[2];//Ϊ�˷���ػ�ȡ���ض����õ�CImage����
    static COLORREF* pData[2];//��������
    int typ;
    int life;
    Enemy();
    Enemy(int w, int h, int passNum, HDC hdc);
    int direc2ImgIdx();
    bool decLife(int attack);//�����Ƿ����ɾ��
    static void initImg(int totW, int totH);
    void blit(HDC mdc,HDC bufdc);
    COLORREF getPixel(int x, int y);
    void move();
    void shoot();
};

#endif