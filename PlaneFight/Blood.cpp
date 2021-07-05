#include "Blood.h"
#include "GameState.h"

extern GameState* gs;

HBITMAP Blood::img = NULL;
CImage Blood::cimg = CImage();
COLORREF* Blood::pData = NULL;

Blood::Blood() : FlyObject() { typ = 0; direcX = 1; moveCount = 0; }

Blood::Blood(int w, int h, HDC hdc) : FlyObject(0, 0, w, h, hdc) {
    typ = 3;
    direcX = 1;
    moveCount = 0;
    v = BLOOD_SPEED;
    x = -w; y = 0;
}

void Blood::initImg(int totW, int totH) {
    if (pData != NULL) return;//用pData是否为空来标识是否已经初始化静态成员
    LPCWSTR path = _T("res/blood.bmp");
    img = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, totW, totH, LR_LOADFROMFILE);
    cimg.Load(path);
    pData = new COLORREF[totW * totH];
    for (int i = 0; i < totW; ++i) {
        for (int j = 0; j < totH; ++j) {
            pData[i * totH + j] = cimg.GetPixel(i, j);
        }
    }
}

void Blood::blit(HDC mdc,HDC bufdc){
    SelectObject(bufdc, img);
    TransparentBlt(mdc, x, y, w, h, bufdc, typ * w, 0, w, h, RGB(0, 0, 0));
}

COLORREF Blood::getPixel(int x, int y) {
    if (pData == NULL) return RGB(0, 0, 0);
    return pData[(w * typ + x) * h + y];
}

bool Blood::move() {
    x += v * direcX;
    y += v / 2;
    if (x > bgW - w) {
        x = bgW - w;
        direcX = -1;
    }
    if (x < 0) {
        x = 0;
        direcX = 1;
    }
    return y >= bgH || (++moveCount) >= 10 * 1000 / FRAME_TIME;
}