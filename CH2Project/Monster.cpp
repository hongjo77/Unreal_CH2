#include "Monster.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include <iostream>

//Github Confirm

Monster::Monster(const string& name, int health, int attack)
    : Name(name), Health(health), Attack(attack) {}

Monster::~Monster() {}

// ��� ���� Getter
string Monster::GetName() const { return Name; }
int Monster::GetHealth() const { return Health; }
int Monster::GetAttack() const { return Attack; }

// �ǰ�
void Monster::TakeDamage(int damage)
{
    Health -= damage;
    if (Health < 0)
    {
        Health = 0;
    }
}

// ���Ͱ� �������� ���
Item* Monster::DropItem() 
{
    int itemType = rand() % 2;
    Item* dropped = nullptr;
    if (itemType == 0)
    {
        dropped = new HealthPotion();
        cout << Name << "��(��) ü�� ������ ����߽��ϴ�!" << endl;
    }
    else
    {
        dropped = new AttackBoost();
        cout << Name << "��(��) ���ݷ� �ν�Ʈ�� ����߽��ϴ�!" << endl;
    }
    return dropped;
}

// �⺻������ ��� ���� ������ �ƴ�
bool Monster::IsBoss() const { return false; }
