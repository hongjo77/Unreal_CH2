#pragma once
#include <string>
#include <vector>
#include "HealthPotion.h"
#include "AttackBoost.h"
#include "Equipment.h"

using namespace std;

// 그리고 장착 인벤토리 넘겨주는 함수 구현해줘야 댐

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
    int Attack;
    int Experience;
    int Gold;
    int MaxMana;
    int CurrentMana;
    Equipment* weapon;
    Equipment* helmet;
    Equipment* chest;
    Equipment* leg;

    vector<Item*> Inventory = {new HealthPotion(), new AttackBoost()};
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
    //장비 초기화
    void InitEquipment();
    //장비들 delete 위한 소멸자
    ~Characters();
    // 장비 스탯 총합
    int GetTotalArmorStat();
    // 장비 목록 넘기기
    vector<Equipment*> GetEquipments();
};
