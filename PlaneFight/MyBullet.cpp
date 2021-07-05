#include "MyBullet.h"
#include "GameState.h"

extern GameState* gs;

HBITMAP MyBullet::img[2] = { NULL,NULL };
CImage MyBullet::cimg[2] = { CImage(),CImage() };
COLORREF* MyBullet::pData[2] = { NULL,NULL };

MyBullet::MyBullet() :Bullet(), isLevelUp(0) {}

MyBullet::MyBullet(int x, int y, bool isLevelUp, HDC hdc) : Bullet(x, y, -1, 0, 0, 25, 0, 0, hdc) {
    this->isLevelUp = isLevelUp;
    w = isLevelUp ? 15 : 20;
    h = isLevelUp ? 30 : 20;
    totIndex = isLevelUp ? 18 : 15;
    initImg();
}

void MyBullet::initImg() {
    if (pData[0] != NULL) return;//用pData[0]是否为空来标识是否已经初始化静态成员
    int totW[2] = { 20 * 15,15 * 18 }, totH[2] = { 20,30 };
    LPCWSTR path[2] = { _T("res/myBullet.bmp"),_T("res/myBullet1.bmp") };
    for (int i = 0; i < 2; ++i) {
        pData[i] = new COLORREF[totW[i] * totH[i]];
        img[i] = (HBITMAP)LoadImage(NULL, path[i], IMAGE_BITMAP, totW[i], totH[i], LR_LOADFROMFILE);
        cimg[i].Load(path[i]);
    }
    for (int idx = 0; idx < 2; ++idx) {
        for (int i = 0; i < totW[idx]; ++i) {
            for (int j = 0; j < totH[idx]; ++j) {
                pData[idx][i * totH[idx] + j] = cimg[idx].GetPixel(i, j);
            }
        }
    }
}

void MyBullet::blit(HDC mdc,HDC bufdc){
    SelectObject(bufdc, img[isLevelUp]);
    TransparentBlt(mdc, x, y, w, h, bufdc, w * index, 0, w, h, RGB(0, 0, 0));
}

COLORREF MyBullet::getPixel(int x, int y) {
    if (pData[0] == NULL) return RGB(0, 0, 0);
    return pData[isLevelUp][(w * index + x) * h + y];
}

int MyBullet::getAttack() {
    return 1 + isLevelUp;
}