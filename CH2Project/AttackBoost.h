#pragma once
#include "Item.h"

using namespace std;

//공격력 증가포션
class AttackBoost : public Item
{
public:
    AttackBoost();
    void Use(Characters& target) override;
};
