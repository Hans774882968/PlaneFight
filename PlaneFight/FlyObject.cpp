#include "FlyObject.h"
#include "GameState.h"

extern GameState* gs;

FlyObject::FlyObject() : x(0), y(0), w(0), h(0), v(0), direc(0) {}

FlyObject::FlyObject(int x, int y, HDC hdc) : x(x), y(y), w(0), h(0), v(0), direc(0), hdc(hdc) {}

FlyObject::FlyObject(int x, int y, int w, int h, HDC hdc) : x(x), y(y), w(w), h(h), v(0), direc(0), hdc(hdc) {}

FlyObject::FlyObject(int x, int y, int w, int h, int v, HDC hdc) : x(x), y(y), w(w), h(h), v(v), direc(0), hdc(hdc) {}

FlyObject::FlyObject(int x, int y, int w, int h, int v, int direc, HDC hdc) : x(x), y(y), w(w), h(h), v(v), direc(direc), hdc(hdc) {}

bool FlyObject::outBound() {
    return (direc == 1 && (y > bgH || x > bgW)) ||
        (direc == -1 && (y < -h) || x > bgW);
}

/*bool FlyObject::collision(FlyObject *other) {//�ϰ棺���ο���ײ���
    return abs((this->x + this->w / 2) - (other->x + other->w / 2)) < abs((this->w + other->w) / 2) &&
        abs((this->y + this->h / 2) - (other->y + other->h / 2)) < abs((this->h + other->h) / 2);
}*/

bool FlyObject::collision(FlyObject* other) {//���ؼ���ײ���
    int thisRight = x + w, thisBottom = y + h,
        otherRight = other->x + other->w, otherBottom = other->y + other->h;
    //���ͼƬ���ཻ�Ļ���������������ײ���
    if (x > otherRight || y > otherBottom || other->x > thisRight || other->y > thisBottom) {
        return false;
    }
    //�����ཻ����ľ��ε����ϽǺ����½����꣬�Լ����εĿ�Ⱥ͸߶�
    int intersectLeft = max(x, other->x), intersectTop = max(y, other->y);
    int intersectRight = min(thisRight, otherRight), intersectBottom = min(thisBottom, otherBottom);
    int intersectWidth = intersectRight - intersectLeft;
    int intersectHeight = intersectBottom - intersectTop;
    //����ͼƬ������ཻ�����ƫ����
    int thisXOffset = intersectLeft - x;
    int thisYOffset = intersectTop - y;
    int otherXOffset = intersectLeft - other->x;
    int otherYOffset = intersectTop - other->y;
    //ȡ���ص����Ͻ�Ϊ��thisXOffset, thisYOffset, otherXOffset, otherYOffset
    //��ȶ�Ϊ��intersectWidth, intersectHeight
    COLORREF bgColor = RGB(0, 0, 0);
    for (int i = 0; i < intersectWidth; ++i) {
        for (int j = 0; j < intersectHeight; ++j) {
            COLORREF c1 = this->getPixel(i + thisXOffset,j + thisYOffset);
            COLORREF c2 = other->getPixel(i + otherXOffset, j + otherYOffset);
            if (c1 != bgColor && c2 != bgColor) return true;
        }
    }
    return false;
}