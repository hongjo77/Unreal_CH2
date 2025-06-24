
#pragma once
#include "Monster.h"

using namespace std;

class BossMonster : public Monster
{
public:
    BossMonster(int level);
    bool IsBoss() const override;
    void OnDeath(Characters& player) override;
    void AttackPlayer(Characters& player) override;
private:
    int SkillAttack;
};
