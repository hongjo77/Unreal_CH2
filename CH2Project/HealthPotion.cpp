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
    //아이템 수량이 음수 값일 때 발생하는 예외 처리문
    try
    {
        if(Amount < 0)
        {
            throw std::invalid_argument("아이템 수량은 음수일 수 없습니다.");
        }
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << RED << "예외 발생: " << e.what() << RESET << endl;
    }
    // 아이템을 소지하지 않고 있을 때 사용하지 않도록 조건문 추가
    if(Amount == 0)
    {
        return;
    }
    // 현재 체력이 최대 체력일 때 아이템을 사용하지 않도록 조건문 추가
    if(target.GetHealth() == target.GetMaxHealth())
    {
        return;
    }
    // 최대 체력 비례 20%의 체력 회복
    int newHealth = target.GetHealth() + target.GetMaxHealth() * 0.2;
    // 초과 회복시 최대 체력으로 설정
    if (newHealth > target.GetMaxHealth())
    {
        newHealth = target.GetMaxHealth();
    }
    std::stringstream oss;
    oss << target.GetName() << "이(가) " << Name << "을 사용하여 20%의 체력을 회복하였습니다! "
        << "(" << target.GetName() << " 체력: " << RED << target.GetHealth() << RESET << " → " << GREEN << newHealth << RESET << ")"
        << " " << GREEN << newHealth - target.GetHealth() << RESET << "회복됨!" << endl;
    GameLog::GetInstance()->PrintAndLog(oss.str());
	// 아이템 수량 감소
    Amount--;
    // 현재 체력 값 설정
    target.SetHealth(newHealth);
}
