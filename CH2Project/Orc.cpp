#include "Orc.h"
#include <iostream>

Orc::Orc(int level)
    : Monster(
        "Orc",
        (rand() % (level * 11)) + (level * 20),
        (rand() % (level * 11)) + (level * 10)
    ) {}


