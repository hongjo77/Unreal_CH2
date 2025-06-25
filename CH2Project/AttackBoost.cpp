#include "AttackBoost.h"
#include "Characters.h"
#include "Color.h"
#include "GameLog.h"
#include <cstdlib>
#include <iostream>
#include <sstream>

//공격력 증가포션 생성자 Name : Attack Boost
AttackBoost::AttackBoost() : Item("Attack Boost", 0) {}

void AttackBoost::Use(Characters& target) 
{
    // 아이템을 소지하지 않고 있을 때 사용하지 않도록 조건문 추가
    if(Amount == 0)
    {
        //std::cout << target.GetName() << "(이)가 " << Name << "을 소지하지 않고 있습니다." << endl;
        return;
    }
    // 공격력 랜덤 증가 10 ~ 50
    int Increase = rand()%50;
    if(Increase < 10)
        Increase = 10;
    int newBaseAttack = target.GetBaseAttack() + Increase;
	std::stringstream oss;
    oss << target.GetName() << "이(가) " << Name << "을(를) 사용하여 공격력이 증가하였습니다! "
        << "(" << target.GetName() << " 공격력: " << RED << target.GetBaseAttack() << RESET << " → " << GREEN << newBaseAttack << RESET << ")"
        << " " << GREEN << Increase << RESET << "증가됨!" << endl;
	GameLog::GetInstance()->PrintAndLog(oss.str());
    // 아이템 수량 감소
    Amount--;
    target.SetAttack(newBaseAttack);
}
