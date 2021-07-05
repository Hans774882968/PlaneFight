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
    static CImage cimg[2];//为了方便地获取像素而设置的CImage对象
    static COLORREF* pData[2];//像素数据
    static HBITMAP protectImg;//保护罩
    int totIndex;//原画数
    int index;//我方飞机动画相关下标
    bool isLevelUp;//是否处于升级状态
    bool isProtected;//是否开启保护罩
    int blood, life;
    MyPlane();
    MyPlane(int x,int y,HDC hdc);
    static void initImg();
    int getV();
    int getIndex();
    int getTotIndex();
    void addBlood();//吃到血包只回血
    bool decLife();//返回值：是否已死亡
    void blit(HDC mdc,HDC bufdc);
    COLORREF getPixel(int x, int y);
    bool moveWithKeyBoard();//返回值：是否进行了移动。
    bool moveWithKeyBoard(WPARAM wParam);//返回值：是否进行了移动。
    void levelUp();
    void levelDown();
    void anime();
    void openProtection();
    void closeProtection();
    void nextPass();//进入下一关时，我方飞机的状态变化
};

#endif