#pragma once
#include "Monster.h"

using namespace std;

class Slime : public Monster
{
public:
    Slime (int level);
    void TextArt() const override;
};
