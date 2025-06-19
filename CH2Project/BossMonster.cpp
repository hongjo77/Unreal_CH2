#include "BossMonster.h"
#include <iostream>

BossMonster::BossMonster(int level)
    : Monster(
        "Orc",
        (rand() % (level * 16)) + (level * 30),
        (rand() % (level * 8)) + (level * 8)
    ) {}

void BossMonster::TakeDamage(int damage) 
{
    Health -= damage;
    if (Health < 0)
    {
        Health = 0;
    }
}

// �������� �ƴ��� Ȯ��
bool BossMonster::IsBoss() const { return true; }
