#include "Characters.h"
#include "Shop.h"
#include <iostream>

Characters* Characters::Instance = nullptr;

Characters::Characters(const string& inName)
    : Name(inName), Level(1), Health(200), MaxHealth(200), Attack(30), Experience(0), Gold(0)
{
    cout << "ĳ���� " << Name << " ���� �Ϸ�! ����: " << Level << ", ü��: " << Health << ", ���ݷ�: " << Attack << endl;
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
    cout << "�̸�: " << Name << " | ����: " << Level << " | ü��: " << Health << "/" << MaxHealth
        << " | ���ݷ�: " << Attack << " | ����ġ: " << Experience << " | ���: " << Gold << endl;
}

void Characters::LevelUp()
{
    // �ִ� ���� 10
    if (Level >= 10)
    {
        return;
    }
    Experience -= 100;
    Level++;
    MaxHealth += Level * 20;
    Attack += Level * 5;
    Health = MaxHealth;
    cout << "������! ���� ����: " << Level << " | ü��: " << MaxHealth << " | ���ݷ�: " << Attack << endl;
}

void Characters::ShowInventory() const
{
    cout << "--- �κ��丮 ---" << endl;
    if (Inventory.empty())
    {
        cout << " (�������)" << endl;
        return;
    }
    // �κ��丮 ������ ���� ���
    for (size_t i = 0; i < Inventory.size(); i++)
    {
        cout << (i + 1) << ". " << Inventory[i]->GetName() << endl;
    }
}

// ��� ���� Getter Setter
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
//gitpush�׽�Ʈ