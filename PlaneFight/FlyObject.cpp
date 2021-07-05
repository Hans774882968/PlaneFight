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

/*bool FlyObject::collision(FlyObject *other) {//老版：矩形框碰撞检测
    return abs((this->x + this->w / 2) - (other->x + other->w / 2)) < abs((this->w + other->w) / 2) &&
        abs((this->y + this->h / 2) - (other->y + other->h / 2)) < abs((this->h + other->h) / 2);
}*/

bool FlyObject::collision(FlyObject* other) {//像素级碰撞检测
    int thisRight = x + w, thisBottom = y + h,
        otherRight = other->x + other->w, otherBottom = other->y + other->h;
    //如果图片不相交的话，不进行像素碰撞检测
    if (x > otherRight || y > otherBottom || other->x > thisRight || other->y > thisBottom) {
        return false;
    }
    //计算相交区域的矩形的左上角和右下角坐标，以及矩形的宽度和高度
    int intersectLeft = max(x, other->x), intersectTop = max(y, other->y);
    int intersectRight = min(thisRight, otherRight), intersectBottom = min(thisBottom, otherBottom);
    int intersectWidth = intersectRight - intersectLeft;
    int intersectHeight = intersectBottom - intersectTop;
    //计算图片相对于相交区域的偏移量
    int thisXOffset = intersectLeft - x;
    int thisYOffset = intersectTop - y;
    int otherXOffset = intersectLeft - other->x;
    int otherYOffset = intersectTop - other->y;
    //取像素的左上角为：thisXOffset, thisYOffset, otherXOffset, otherYOffset
    //宽度都为：intersectWidth, intersectHeight
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