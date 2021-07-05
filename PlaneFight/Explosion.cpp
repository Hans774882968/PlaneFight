#include "Explosion.h"
#include "GameState.h"

extern GameState* gs;

HBITMAP Explosion::img = NULL;

Explosion::Explosion() :FlyObject() { index = totIndex = 0; }

Explosion::Explosion(int x, int y, HDC hdc) : FlyObject(x, y, hdc) {
    w = 66; h = 66;
    index = 0; totIndex = 8;
}

void Explosion::initImg() {
    int totW = 528, totH = 66;
    LPCWSTR path = _T("res/explosion.dib");
    img = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, totW, totH, LR_LOADFROMFILE);
}

void Explosion::blit(HDC mdc, HDC bufdc) {
    SelectObject(bufdc, img);
    TransparentBlt(mdc, x, y, w, h, bufdc, w * index, 0, w, h, RGB(0, 0, 0));
}

COLORREF Explosion::getPixel(int x, int y) { return RGB(0, 0, 0); }

bool Explosion::anime() {
    bool end = (index + 1 == totIndex);
    index = (index + 1) % totIndex;
    return end;
}