// header.h: 标准系统包含文件的包含文件，
// 或特定于项目的包含文件
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>
// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <vector>
#include <atlimage.h>
#include "utils.h"

#define bgW ((gs->rect).Width())
#define bgH ((gs->rect).Height())
const int FRAME_TIME = 50;//50ms一帧
const int BG_SPEED = 2;//背景移动速度
const int MY_BLOOD = 10;//我方飞机血量
const int CD_TIME = 30;//我方飞机技能的统一CD
const unsigned int ENEMY_NUM = 20;
const int ENEMY_SPEED = 7;//敌人初始速度
const int ENEMY_W = 60, ENEMY_H = 45;
const int MYBULLET_W = 20, MYBULLET_H = 20;
const int ENEMYBULLET_W = 6, ENEMYBULLET_H = 16;
const int PROTECT_W = 80, PROTECT_H = 80;
const int BLOOD_W = 40, BLOOD_H = 40;
const int BLOOD_SPEED = 4;
const int ME_TOT_BLOOD = 10;