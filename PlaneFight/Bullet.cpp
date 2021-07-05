#include "Bullet.h"
#include "GameState.h"

extern GameState* gs;

Bullet::Bullet() :FlyObject() { index = totIndex = 0; direc = 0; }

//initIndex表示不同类型的敌人发射的子弹
Bullet::Bullet(int x, int y, int direc, int w, int h, int v,
    int initIndex, int totIndex, HDC hdc) : FlyObject(x, y, w, h, v, direc, hdc), index(initIndex), totIndex(totIndex) {}

void Bullet::initImg(int totW, int totH, LPCWSTR path) {}
void Bullet::initImg() {}

void Bullet::move() {
    y += v * direc;
}

void Bullet::anime() {
    index = rand() % totIndex;
}