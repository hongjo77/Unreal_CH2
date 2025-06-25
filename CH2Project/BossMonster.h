#pragma once
#include "Monster.h"
#include <random> //mt19937, uniform_int_distribution
#include <chrono> //시드용

using namespace std;

class BossMonster : public Monster
{
public:
    BossMonster(int level);
    bool IsBoss() const override;
    void OnDeath(Characters& player) override;
    void AttackPlayer(Characters& player) override;
    void TextArt() const override;
private:
    int SkillAttack;
    mt19937 rng;
    uniform_int_distribution<int> chanceDistribution;
};
