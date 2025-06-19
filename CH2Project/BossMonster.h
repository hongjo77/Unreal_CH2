#pragma once
#include "Monster.h"

using namespace std;

class BossMonster : public Monster
{
public:
    BossMonster(int level);
    void TakeDamage(int damage) override;
    bool IsBoss() const override;
};
