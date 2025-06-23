#pragma once
#include <string>
#include <vector>
#include "Item.h"

using namespace std;

// 무기 공격력 계산식 캐릭터 내부에서 구현할 것 
// 사빈씨가 구현해준 무기 클래스 바탕으로 계산하기
enum class AttackType
{
    Normal,
    FireBall,
    Strike
};

class Characters
{
private:
    static Characters* Instance;
    string Name;
    int Level;
    int Health;
    int MaxHealth;
    int Attack;// 무기 공격력 계산식 해야됨
    int Experience;
    int Gold;
    int MaxMana;
    int CurrentMana;
    vector<Item*> Inventory;

    AttackType currentAttackType = AttackType::Normal;

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
    void SetAttack(int newAttack);
    int GetLevel() const;
    void SetLevel(int newLevel);
    int GetExperience() const;
    void SetExperience(int newExp);
    int GetGold() const;
    void SetGold(int newGold);
    vector<Item*>& GetInventory();
    int GetAttack();
    //랜덤한 스킬 선택
    int RandomSkill();
};
