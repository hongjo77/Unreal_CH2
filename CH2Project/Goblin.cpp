#include "Goblin.h"
#include <iostream>

Goblin::Goblin(int level)
    : Monster(
        "Goblin",
        (rand() % (level * 11)) + (level * 20),
        (rand() % (level * 6)) + (level * 5)
    ) {}

void Goblin::TakeDamage(int damage)
{
    Health -= damage;
    if (Health < 0) 
    {
        Health = 0;
    }
}
