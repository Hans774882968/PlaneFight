#include "EnemyBullet.h"
#include "GameState.h"

extern GameState* gs;

HBITMAP EnemyBullet::img[2] = { NULL,NULL };
CImage EnemyBullet::cimg[2] = { CImage(),CImage() };
COLORREF* EnemyBullet::pData[2] = { NULL,NULL };

EnemyBullet::EnemyBullet() : Bullet() { index = totIndex = 0; direc = 0; }

//typ表示不同类型的敌人发射的子弹
EnemyBullet::EnemyBullet(int x, int y, int direc, int w, int h, int v, int typ, HDC hdc) : Bullet(x, y, direc, w, h, v, typ, 5, hdc){
    initImg();
}

int EnemyBullet::direc2ImgIdx() {
    return direc == -1;
}

void EnemyBullet::initImg() {
    if (pData[0] != NULL) return;//用pData[0]是否为空来标识是否已经初始化静态成员
    int totW = ENEMYBULLET_W * totIndex, totH = ENEMYBULLET_H;
    LPCWSTR path[2] = { _T("res/enemyBulletDown.bmp"),_T("res/enemyBulletUp.bmp") };
    for (int i = 0; i < 2; ++i) {
        pData[i] = new COLORREF[totW * totH];
        img[i] = (HBITMAP)LoadImage(NULL, path[i], IMAGE_BITMAP, totW, totH, LR_LOADFROMFILE);
        cimg[i].Load(path[i]);
    }
    for (int idx = 0; idx < 2; ++idx) {
        for (int i = 0; i < totW; ++i) {
            for (int j = 0; j < totH; ++j) {
                pData[idx][i * totH + j] = cimg[idx].GetPixel(i, j);
            }
        }
    }
}

void EnemyBullet::blit(HDC mdc,HDC bufdc){
    SelectObject(bufdc, img[direc2ImgIdx()]);
    TransparentBlt(mdc, x, y, w, h, bufdc, w * index, 0, w, h, RGB(0, 0, 0));
}

COLORREF EnemyBullet::getPixel(int x, int y) {
    if (pData[0] == NULL) return RGB(0, 0, 0);
    return pData[direc2ImgIdx()][(w * index + x) * h + y];
}