#pragma once
#ifndef EnemyBullet_H
#define EnemyBullet_H

#include "framework.h"
#include "Bullet.h"

class GameState;

class EnemyBullet: public Bullet{
public:
    static HBITMAP img[2];
    static CImage cimg[2];//Ϊ�˷���ػ�ȡ���ض����õ�CImage����
    static COLORREF* pData[2];//��������
    EnemyBullet();
    EnemyBullet(int x, int y, int direc, int w, int h, int v, int typ, HDC hdc);//typ��ʾ��ͬ���͵ĵ��˷�����ӵ�
    int direc2ImgIdx();
    void initImg();
    void blit(HDC mdc,HDC bufdc);
    COLORREF getPixel(int x, int y);
};

#endif