#pragma once
#ifndef MyPlane_H
#define MyPlane_H
#include "framework.h"
#include <mmsystem.h>
#include "FlyObject.h"

class GameState;

class MyPlane: public FlyObject{
public:
    static HBITMAP img[2];
    static CImage cimg[2];//Ϊ�˷���ػ�ȡ���ض����õ�CImage����
    static COLORREF* pData[2];//��������
    static HBITMAP protectImg;//������
    int totIndex;//ԭ����
    int index;//�ҷ��ɻ���������±�
    bool isLevelUp;//�Ƿ�������״̬
    bool isProtected;//�Ƿ���������
    int blood, life;
    MyPlane();
    MyPlane(int x,int y,HDC hdc);
    static void initImg();
    int getV();
    int getIndex();
    int getTotIndex();
    void addBlood();//�Ե�Ѫ��ֻ��Ѫ
    bool decLife();//����ֵ���Ƿ�������
    void blit(HDC mdc,HDC bufdc);
    COLORREF getPixel(int x, int y);
    bool moveWithKeyBoard();//����ֵ���Ƿ�������ƶ���
    bool moveWithKeyBoard(WPARAM wParam);//����ֵ���Ƿ�������ƶ���
    void levelUp();
    void levelDown();
    void anime();
    void openProtection();
    void closeProtection();
    void nextPass();//������һ��ʱ���ҷ��ɻ���״̬�仯
};

#endif