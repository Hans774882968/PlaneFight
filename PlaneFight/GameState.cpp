#include "GameState.h"

GameState::GameState(HWND hWnd) {
    hdc = GetDC(hWnd);
    SetStretchBltMode(hdc, COLORONCOLOR);
    mdc = CreateCompatibleDC(hdc);
    bufdc = CreateCompatibleDC(hdc);
    GetClientRect(hWnd, &rect);
    resizeDC(hdc, mdc, rect.Width(), rect.Height());
    bgPrepare();
    loading.Load(_T("res/loading.gif"));
    drawLoading();
    me = new MyPlane((rect.Width() - 60) / 2, rect.Height() - 45 - 100, hdc);
    MyPlane::initImg();
    Enemy::initImg(ENEMY_W * 5, ENEMY_H);
    Explosion::initImg();
    Blood::initImg(BLOOD_W * 6, BLOOD_H);
    curY = 0;
}

void GameState::bgPrepare() {//每次修改passNum后调用
    if (!bg.IsNull()) {//非空，表示进入下一关
        bg.Destroy();
        bg = CImage();
    }
    WCHAR bgFile[30];
    wsprintf(bgFile, L"res/background%d.bmp", sb.passNum);
    bg.Load(bgFile);
    bg.StretchBlt(hdc, rect, SRCCOPY);
}

bool GameState::isBossPeriod() {
    return sb.bossPeriod;
}

void GameState::moveBg() {
    curY += BG_SPEED;
    if (curY >= rect.Height()) curY = 0;
}

void GameState::updateBg() {
    bg.TransparentBlt(mdc, CRect(0, curY - rect.Height(), rect.Width(), curY), SRCCOPY);
    bg.TransparentBlt(mdc, CRect(0, curY, rect.Width(), curY + rect.Height()), SRCCOPY);
}

void GameState::drawLoading() {
    loading.TransparentBlt(hdc,
        CRect((rect.Width() - 166) / 2, (rect.Height() - 166) / 2,
        (rect.Width() + 166) / 2, (rect.Height() + 166) / 2), RGB(255, 255, 255));
}