#pragma once
#ifndef SkillCD_H
#define SkillCD_H

#include "framework.h"

class GameState;

class SkillCD{
private:
    int CD;
public:
    SkillCD();
    static int totCD();
    int getProcess();
    bool canUseSkill();
    void useSkillCD();
    bool updateSkillCD();
};

#endif