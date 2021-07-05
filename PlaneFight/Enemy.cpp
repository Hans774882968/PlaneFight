#include "Enemy.h"
#include "GameState.h"

extern GameState* gs;

HBITMAP Enemy::img[2] = { NULL,NULL };
CImage Enemy::cimg[2] = { CImage(),CImage() };
COLORREF* Enemy::pData[2] = { NULL,NULL };

Enemy::Enemy() : FlyObject() { typ = 0; direc = 0; life = 0; }

Enemy::Enemy(int w, int h, int passNum, HDC hdc) : FlyObject(0, 0, w, h, hdc) {
    typ = rndInt(0, 4);
    v = ENEMY_SPEED + passNum;
    //v = 0;//dbg
    if (passNum > 4) direc = rand() % 2 ? 1 : -1;
    else direc = 1;
    x = rndInt(0, bgW - w - 1);
    if (direc == 1) y = -h * 2;
    else y = bgH + h * 2;
    //y = 500;//dbg
    life = 2;
}

int Enemy::direc2ImgIdx() {
    return direc == -1;
}

bool Enemy::decLife(int attack) {
    life -= attack;
    return life <= 0;
}

void Enemy::initImg(int totW, int totH) {
    if (pData[0] != NULL) return;//用pData[0]是否为空来标识是否已经初始化静态成员
    LPCWSTR path0 = _T("res/enemyDown.bmp"), path1 = _T("res/enemyUp.bmp");
    img[0] = (HBITMAP)LoadImage(NULL, path0, IMAGE_BITMAP, totW, totH, LR_LOADFROMFILE);
    img[1] = (HBITMAP)LoadImage(NULL, path1, IMAGE_BITMAP, totW, totH, LR_LOADFROMFILE);
    cimg[0].Load(path0); cimg[1].Load(path1);
    for (int idx = 0; idx < 2; ++idx) {
        pData[idx] = new COLORREF[totW * totH];
        for (int i = 0; i < totW; ++i) {
            for (int j = 0; j < totH; ++j) {
                pData[idx][i * totH + j] = cimg[idx].GetPixel(i, j);
            }
        }
    }
}

void Enemy::blit(HDC mdc,HDC bufdc){
    SelectObject(bufdc, img[direc2ImgIdx()]);
    TransparentBlt(mdc, x, y, w, h, bufdc, typ * w, 0, w, h, RGB(0, 0, 0));
}

COLORREF Enemy::getPixel(int x, int y) {
    if (pData == NULL) return RGB(0, 0, 0);
    return pData[direc2ImgIdx()][(w * typ + x) * h + y];
}

void Enemy::move() {
    y += v * direc;
}

void Enemy::shoot() {
    if (gs == NULL) return;
    int bulletX = x + (w - ENEMYBULLET_W) / 2,bulletY = y + direc * h;
    gs->enemyBullets.push_back(EnemyBullet(
        bulletX, bulletY, direc, ENEMYBULLET_W, ENEMYBULLET_H, 10 + gs->sb.passNum - 1, typ, gs->hdc));
}