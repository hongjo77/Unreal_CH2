#pragma once
#include "Characters.h"
#include "Monster.h"
#include "BossMonster.h"
#include "Shop.h"

using namespace std;

class GameManager
{
private:
    Shop shopInstance;

public:
    Monster* GenerateMonster(int level);
    BossMonster* GenerateBossMonster(int level);
    void Battle(Characters& player, Monster& enemy);
    void VisitShop(Characters& player);
    void DisplayInventory(Characters& player);
};
