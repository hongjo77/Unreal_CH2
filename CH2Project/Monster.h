#pragma once
#include <string>
#include "Item.h"
#include "Characters.h"
#include <cstdlib>
#include <ctime>

#define COLOR_RESET "\x1b[0m"
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"

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
    virtual void OnDeath(Characters& player);
    virtual int DropItem();
    virtual void AttackPlayer(Characters& player);
    virtual bool IsBoss() const;
    virtual bool IsGoldenGoblin() const;
};
