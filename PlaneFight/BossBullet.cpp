#include "BossBullet.h"
#include "GameState.h"

extern GameState* gs;

HBITMAP BossBullet::img = NULL;
CImage BossBullet::cimg = CImage();
COLORREF* BossBullet::pData = NULL;

BossBullet::BossBullet() : Bullet() {}

BossBullet::BossBullet(int x, int y, int w, int h, HDC hdc) : Bullet(x, y, 1, w, h, 25, 0, 18, hdc) {
    initImg(w * 18, h, _T("res/bossBullet.bmp"));
}

void BossBullet::initImg(int totW, int totH, LPCWSTR path) {
    if (pData != NULL) return;//用pData是否为空来标识是否已经初始化静态成员
    pData = new COLORREF[totW * totH];
    img = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, totW, totH, LR_LOADFROMFILE);
    cimg.Load(path);
    for (int i = 0; i < totW; ++i) {
        for (int j = 0; j < totH; ++j) {
            pData[i * totH + j] = cimg.GetPixel(i, j);
        }
    }
}

void BossBullet::blit(HDC mdc, HDC bufdc) {
    SelectObject(bufdc, img);
    TransparentBlt(mdc, x, y, w, h, bufdc, w * index, 0, w, h, RGB(0, 0, 0));
}

COLORREF BossBullet::getPixel(int x, int y) {
    if (pData == NULL) return RGB(0, 0, 0);
    return pData[(w * index + x) * h + y];
}