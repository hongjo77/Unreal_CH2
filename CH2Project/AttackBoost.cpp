#include "AttackBoost.h"
#include "Characters.h"
#include <iostream>

AttackBoost::AttackBoost() : Item("Attack Boost") {}

void AttackBoost::Use(Characters& target) 
{
    // 공격력 10 증가
    target.SetAttack(target.GetAttack() + 10);
    cout << target.GetName() << "가 " << Name << "을 사용했습니다. " 
        << target.GetName() << "공격력이 10만큼 증가하였습니다! 현재 공격력: " 
        << target.GetAttack() << endl;
}
