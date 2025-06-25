#pragma once
#include "Characters.h"
#include "Monster.h"
#include "BossMonster.h"
#include "Shop.h"
#define COLOR_RESET "\x1b[0m"
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"

using namespace std;

class GameManager
{
private:
    Shop shopInstance;
    int BattleCount = 1;

public:
    Monster* GenerateMonster(int level);
    BossMonster* GenerateBossMonster(int level);
    void Battle(Characters& player, Monster& enemy);
    void VisitShop(Characters& player);
    void DisplayInventory(Characters& player);
};
