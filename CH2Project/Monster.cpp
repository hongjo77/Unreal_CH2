#include "Monster.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include <iostream>

//Github Confirm

Monster::Monster(const string& name, int health, int attack)
    : Name(name), Health(health), Attack(attack) {}

Monster::~Monster() {}

// 멤버 변수 Getter
string Monster::GetName() const { return Name; }
int Monster::GetHealth() const { return Health; }
int Monster::GetAttack() const { return Attack; }

// 피격
void Monster::TakeDamage(int damage)
{
    Health -= damage;
    if (Health < 0)
    {
        Health = 0;
    }
}

// 몬스터가 아이템을 드랍
Item* Monster::DropItem() 
{
    int itemType = rand() % 2;
    Item* dropped = nullptr;
    if (itemType == 0)
    {
        dropped = new HealthPotion();
        cout << Name << "이(가) 체력 포션을 드랍했습니다!" << endl;
    }
    else
    {
        dropped = new AttackBoost();
        cout << Name << "이(가) 공격력 부스트를 드랍했습니다!" << endl;
    }
    return dropped;
}

// 기본적으로 모든 적은 보스가 아님
bool Monster::IsBoss() const { return false; }
