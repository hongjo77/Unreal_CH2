#include "HealthPotion.h"
#include "Characters.h"
#include <iostream>

HealthPotion::HealthPotion() : Item("Health Potion") {}

void HealthPotion::Use(Characters& target)
{
    // 50��ŭ ȸ��
    int newHealth = target.GetHealth() + 50;
    // �ʰ� ȸ���� �ִ� ü������ ����
    if (newHealth > target.GetMaxHealth())
    {
        newHealth = target.GetMaxHealth();
    }
    target.SetHealth(newHealth);
    cout << target.GetName() << "�� " << Name << "�� ����߽��ϴ�. "
        << target.GetName() << " ü��: " << target.GetHealth() << endl;
}
