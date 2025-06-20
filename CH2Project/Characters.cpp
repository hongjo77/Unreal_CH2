#include "Characters.h"
#include "Shop.h"
#include <iostream>

Characters* Characters::Instance = nullptr;

Characters::Characters(const string& inName)
    : Name(inName), Level(1), Health(200), MaxHealth(200), Attack(30), Experience(0), Gold(0)
{
    cout << "캐릭터 " << Name << " 생성 완료! 레벨: " << Level << ", 체력: " << Health << ", 공격력: " << Attack << endl;
    cout << endl;
}

Characters* Characters::GetInstance(const string& inName)
{
    if (!Instance)
    {
        Instance = new Characters(inName);
    }
    return Instance;
}

string Characters::GetName() const { return Name; }

void Characters::DisplayStatus() const
{
    cout << "이름: " << Name << " | 레벨: " << Level << " | 체력: " << Health << "/" << MaxHealth
        << " | 공격력: " << Attack << " | 경험치: " << Experience << " | 골드: " << Gold << endl;
}

void Characters::LevelUp()
{
    // 최대 레벨 10
    if (Level >= 10)
    {
        return;
    }
    Experience -= 100;
    Level++;
    MaxHealth += Level * 20;
    Attack += Level * 5;
    Health = MaxHealth;
    cout << "레벨업! 현재 레벨: " << Level << " | 체력: " << MaxHealth << " | 공격력: " << Attack << endl;
}

void Characters::ShowInventory() const
{
    cout << "--- 인벤토리 ---" << endl;
    if (Inventory.empty())
    {
        cout << " (비어있음)" << endl;
        return;
    }
    // 인벤토리 아이템 전부 출력
    for (size_t i = 0; i < Inventory.size(); i++)
    {
        cout << (i + 1) << ". " << Inventory[i]->GetName() << endl;
    }
}

// 멤버 변수 Getter Setter
int Characters::GetHealth() const { return Health; }
void Characters::SetHealth(int newHealth) { Health = newHealth; }
int Characters::GetMaxHealth() const { return MaxHealth; }
int Characters::GetAttack() const { return Attack; }
void Characters::SetAttack(int newAttack) { Attack = newAttack; }
int Characters::GetLevel() const { return Level; }
void Characters::SetLevel(int newLevel) { Level = newLevel; }
int Characters::GetExperience() const { return Experience; }
void Characters::SetExperience(int newExp) { Experience = newExp; }
int Characters::GetGold() const { return Gold; }
void Characters::SetGold(int newGold) { Gold = newGold; }
vector<Item*>& Characters::GetInventory() { return Inventory; }
//gitpush테스트
//testmerge