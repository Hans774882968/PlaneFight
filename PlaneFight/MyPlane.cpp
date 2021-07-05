#include "MyPlane.h"
#include "GameState.h"

extern GameState* gs;

HBITMAP MyPlane::img[2] = { NULL,NULL };
CImage MyPlane::cimg[2] = { CImage(),CImage() };
COLORREF* MyPlane::pData[2] = { NULL,NULL };
HBITMAP MyPlane::protectImg = NULL;

MyPlane::MyPlane() :FlyObject() { index = 0; totIndex = 0; isLevelUp = isProtected = false; blood = life = 0; }

MyPlane::MyPlane(int x,int y, HDC hdc):FlyObject(x,y,hdc){
    blood = MY_BLOOD; life = 3; isProtected = false;
    levelDown();
}

void MyPlane::initImg() {
    if (pData[0] != NULL) return;//用pData[0]是否为空来标识是否已经初始化静态成员
    int totW[2] = { 60 * 4,60 * 14 }, totH[2] = { 45,75 };
    LPCWSTR path[2] = { _T("res/me.bmp"), _T("res/me1.bmp") };
    for (int i = 0; i < 2; ++i) {
        img[i] = (HBITMAP)LoadImage(NULL, path[i], IMAGE_BITMAP, totW[i], totH[i], LR_LOADFROMFILE);
        cimg[i].Load(path[i]);
    }
    for (int idx = 0; idx < 2; ++idx) {
        pData[idx] = new COLORREF[totW[idx] * totH[idx]];
        for (int i = 0; i < totW[idx]; ++i) {
            for (int j = 0; j < totH[idx]; ++j) {
                pData[idx][i * totH[idx] + j] = cimg[idx].GetPixel(i, j);
            }
        }
    }
    protectImg = (HBITMAP)LoadImage(NULL, _T("res/protect.bmp"), IMAGE_BITMAP, PROTECT_W, PROTECT_H, LR_LOADFROMFILE);
}

int MyPlane::getV() {
    return isLevelUp ? 18 : 12;
}

int MyPlane::getIndex() {
    return isLevelUp ? 0 : 3;
}

int MyPlane::getTotIndex() {
    return isLevelUp ? 14 : 4;
}

void MyPlane::addBlood() {
    blood = min(blood + 5, ME_TOT_BLOOD);
}

bool MyPlane::decLife() {
    if (isProtected) return life <= 0;//如果开启保护罩，则不减少生命——setter的应用。
    if (--(blood) <= 0) {
        --life;
        blood = ME_TOT_BLOOD;
    }
    return life <= 0;
}

void MyPlane::blit(HDC mdc,HDC bufdc){
    if (isProtected) {
        SelectObject(bufdc, protectImg);
        TransparentBlt(mdc, x - PROTECT_W / 2 + w / 2, y - PROTECT_H / 2 + h / 2, PROTECT_W, PROTECT_H,
            bufdc, 0, 0, PROTECT_W, PROTECT_H, RGB(255, 255, 255));
    }
    SelectObject(bufdc, img[isLevelUp]);
    TransparentBlt(mdc, x, y, w, h, bufdc, w * index, 0, w, h, RGB(0, 0, 0));
}

COLORREF MyPlane::getPixel(int x, int y) {
    if (pData[0] == NULL) return RGB(0, 0, 0);
    return pData[isLevelUp][(w * index + x) * h + y];
}

bool MyPlane::moveWithKeyBoard() {//返回值：是否进行了移动。
    if ((GetAsyncKeyState(VK_UP) & 0x8000) == 0x8000 || (GetAsyncKeyState('W') & 0x8000) == 0x8000) {
        y = max(y - v, 0);
        return true;
    }
    if ((GetAsyncKeyState(VK_DOWN) & 0x8000) == 0x8000 || (GetAsyncKeyState('S') & 0x8000) == 0x8000) {
        y = min(y + v, bgH - h);
        return true;
    }
    if ((GetAsyncKeyState(VK_LEFT) & 0x8000) == 0x8000 || (GetAsyncKeyState('A') & 0x8000) == 0x8000) {
        x = max(x - v, 0);
        return true;
    }
    if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) == 0x8000 || (GetAsyncKeyState('D') & 0x8000) == 0x8000) {
        x = min(x + v, bgW - w);
        return true;
    }
    return false;
}

bool MyPlane::moveWithKeyBoard(WPARAM wParam) {//返回值：是否进行了移动。
    if (wParam == VK_UP || wParam == 'W') {
        y = max(y - v, 0);
        return true;
    }
    else if (wParam == VK_DOWN || wParam == 'S') {
        y = min(y + v, bgH - h);
        return true;
    }
    else if (wParam == VK_LEFT || wParam == 'A') {
        x = max(x - v, 0);
        return true;
    }
    else if (wParam == VK_RIGHT || wParam == 'D') {
        x = min(x + v, bgW - w);
        return true;
    }
    return false;
}

void MyPlane::levelUp() {
    isLevelUp = true;
    v = getV();
    index = getIndex(); totIndex = getTotIndex();
    w = 60; h = 75;
}

void MyPlane::levelDown() {
    isLevelUp = false;
    v = getV();
    index = getIndex(); totIndex = getTotIndex();
    w = 60; h = 45;
}

void MyPlane::anime() {
    if (!isLevelUp) return;
    index = (index + 1) % totIndex;
}

void MyPlane::openProtection() {
    isProtected = true;
}

void MyPlane::closeProtection() {
    isProtected = false;
}

void MyPlane::nextPass() {
    blood = MY_BLOOD; life = 3;
    levelDown();
    closeProtection();
}