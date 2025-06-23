#include "AttackBoost.h"
#include "Characters.h"
#include <iostream>

//공격력 증가포션 생성자 Name : Attack Boost
AttackBoost::AttackBoost() : Item("Attack Boost", 0) {}

void AttackBoost::Use(Characters& target) 
{
    // 아이템을 소지하지 않고 있을 때 사용하지 않도록 조건문 추가
    if(Amount == 0)
    {
        std::cout << target.GetName() << "(이)가 " << Name << "을 소지하지 않고 있습니다." << endl;
        return;
    }
    // 공격력 10 증가 
    target.SetAttack(target.GetAttack() + 10);
    // 아이템 수량 감소
    Amount--;
    std::cout << target.GetName() << "가 " << Name << "을 사용했습니다. " 
        << target.GetName() << "공격력이 10만큼 증가하였습니다! 현재 공격력: " 
        << target.GetAttack() << endl;
}
