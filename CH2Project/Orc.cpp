#include "Orc.h"
#include <iostream>

Orc::Orc(int level)
    : Monster(
        "Orc",
        (rand() % (level * 11)) + (level * 20),
        (rand() % (level * 6)) + (level * 5)
    ) {}

void Orc::TakeDamage(int damage) 
{
    Health -= damage;
    if (Health < 0)
    {
        Health = 0;
    }
}
