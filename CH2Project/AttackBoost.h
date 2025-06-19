#pragma once
#include "Item.h"

using namespace std;

class AttackBoost : public Item
{
public:
    AttackBoost();
    void Use(Characters& target) override;
};
