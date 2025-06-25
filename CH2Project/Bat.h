#pragma once
#include "Monster.h"

using namespace std;

class Bat : public Monster
{
public:
    Bat(int level);
    void TextArt() const override;
};
