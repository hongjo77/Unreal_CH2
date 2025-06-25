#pragma once
#include "Monster.h"

using namespace std;

class Orc : public Monster
{
public:
    Orc(int level);
    void TextArt() const override;
};
