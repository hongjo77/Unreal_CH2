#pragma once
#include "Item.h"

using namespace std;

class HealthPotion : public Item
{
public:
    HealthPotion();
    void Use(Characters& target) override;
};
