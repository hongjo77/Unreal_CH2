#include "AttackBoost.h"
#include "Characters.h"
#include <iostream>

AttackBoost::AttackBoost() : Item("Attack Boost") {}

void AttackBoost::Use(Characters& target) 
{
    // ���ݷ� 10 ����
    target.SetAttack(target.GetAttack() + 10);
    cout << target.GetName() << "�� " << Name << "�� ����߽��ϴ�. " 
        << target.GetName() << "���ݷ��� 10��ŭ �����Ͽ����ϴ�! ���� ���ݷ�: " 
        << target.GetAttack() << endl;
}
