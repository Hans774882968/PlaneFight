#include "utils.h"

int rndInt(int a, int b) {
    if (a == b) return a;
    return rand() % (b - a + 1) + a;
}

void resizeDC(HDC hdc, HDC mdc, int w, int h) {
    HBITMAP bmp = CreateCompatibleBitmap(hdc, w, h);
    SelectObject(mdc, bmp);
}