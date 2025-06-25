#pragma once
#include "Item.h"

//체력포션
class HealthPotion : public Item
{
public:
    HealthPotion();
    void Use(Characters& target) override;
};
