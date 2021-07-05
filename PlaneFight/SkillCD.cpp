#include "SkillCD.h"
#include "GameState.h"

extern GameState* gs;

SkillCD::SkillCD() { CD = totCD(); }

int SkillCD::totCD() {
    return 1000 / FRAME_TIME * CD_TIME;
}

int SkillCD::getProcess() {
    return CD / (1000 / FRAME_TIME);
}

bool SkillCD::canUseSkill() {
    return CD >= totCD();
}

void SkillCD::useSkillCD() {
    CD = 0;
}

bool SkillCD::updateSkillCD() {
    if (canUseSkill()) return true;
    return (++CD) >= totCD();
}