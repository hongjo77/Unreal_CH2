#include "Troll.h"
#include <iostream>

Troll::Troll(int level)
    : Monster(
        "Troll",
        (rand() % (level * 11)) + (level * 20),
        (rand() % (level * 6)) + (level * 5)
    ) {}

void Troll::TakeDamage(int damage) 
{
    Health -= damage;
    if (Health < 0)
    {
        Health = 0;
    }
}
