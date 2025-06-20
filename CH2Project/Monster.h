#pragma once
#include <string>
#include "Item.h"
#include <cstdlib>
#include <ctime>

using namespace std;

class Monster
{
protected:
    string Name;
    int Health;
    int Attack;

public:
    Monster(const string& name, int health, int attack);
    virtual ~Monster();

    virtual string GetName() const;
    virtual int GetHealth() const;
    virtual int GetAttack() const;
    virtual void TakeDamage(int damage);
    virtual Item* DropItem();
    virtual bool IsBoss() const;
};
