#pragma once
#include <string>
#include <vector>
#include "Item.h"

using namespace std;

class Characters
{
private:
    static Characters* Instance;
    string Name;
    int Level;
    int Health;
    int MaxHealth;
    int Attack;
    int Experience;
    int Gold;
    vector<Item*> Inventory;

protected:
    Characters(const string& inName);

public:
    static Characters* GetInstance(const string& inName = "");

    string GetName() const;
    void DisplayStatus() const;
    void LevelUp();
    void ShowInventory() const;

    int GetHealth() const;
    void SetHealth(int newHealth);
    int GetMaxHealth() const;
    int GetAttack() const;
    void SetAttack(int newAttack);
    int GetLevel() const;
    void SetLevel(int newLevel);
    int GetExperience() const;
    void SetExperience(int newExp);
    int GetGold() const;
    void SetGold(int newGold);
    vector<Item*>& GetInventory();
};
