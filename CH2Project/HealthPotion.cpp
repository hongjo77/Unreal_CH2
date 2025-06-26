#include "HealthPotion.h"
#include "Characters.h"
#include "Color.h"
#include "GameLog.h"
#include <iostream>
#include <sstream>

// 체력포션 생성자 초기값 [ Name : Health Potion, Amount : 0 ]
HealthPotion::HealthPotion() : Item("Health Potion", 0) {}

void HealthPotion::Use(Characters& target)
{
	std::stringstream oss;
    // 아이템을 소지하지 않고 있을 때 사용하지 않도록 조건문 추가
    if(Amount == 0)
    {
        //std::cout << target.GetName() << "이(가) " << Name << "을 소지하지 않고 있습니다." << endl;
        return;
    }
    // 현재 체력이 최대 체력일 때 아이템을 사용하지 않도록 조건문 추가
    if(target.GetHealth() == target.GetMaxHealth())
    {
        //std::cout << target.GetName() << "(은)는 이미 최대 체력입니다." << endl;
        return;
    }
    // 최대 체력 비례 20%의 체력 회복
    int newHealth = target.GetHealth() + target.GetMaxHealth() * 0.2;
    // 초과 회복시 최대 체력으로 설정
    if (newHealth > target.GetMaxHealth())
    {
        newHealth = target.GetMaxHealth();
    }
    oss << target.GetName() << "이(가) " << Name << "을 사용하여 20%의 체력을 회복하였습니다! "
        << "(" << target.GetName() << " 체력: " << RED << target.GetHealth() << RESET << " → " << GREEN << newHealth << RESET << ")"
        << " " << GREEN << newHealth - target.GetHealth() << RESET << "회복됨!" << endl;
    GameLog::GetInstance()->PrintAndLog(oss.str());
	// 아이템 수량 감소
    Amount--;
    // 현재 체력 값 설정
    target.SetHealth(newHealth);
}
