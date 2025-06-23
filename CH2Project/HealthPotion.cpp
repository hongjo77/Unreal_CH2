#include "HealthPotion.h"
#include "Characters.h"

// 체력포션 생성자 초기값 [ Name : Health Potion, Amount : 0 ]
HealthPotion::HealthPotion() : Item("Health Potion", 0) {}

void HealthPotion::Use(Characters& target)
{
    // 아이템을 소지하지 않고 있을 때 사용하지 않도록 조건문 추가
    if(Amount == 0)
    {
        std::cout << target.GetName() << "(이)가 " << Name << "을 소지하지 않고 있습니다." << endl;
        return;
    }
    // 현재 체력이 최대 체력일 때 아이템을 사용하지 않도록 조건문 추가
    if(target.GetHealth() == target.GetMaxHealth())
    {
        std::cout << target.GetName() << "(은)는 이미 최대 체력입니다." << endl;
        return;
    }
    // 50만큼 회복
    int newHealth = target.GetHealth() + 50;
    // 초과 회복시 최대 체력으로 설정
    if (newHealth > target.GetMaxHealth())
    {
        newHealth = target.GetMaxHealth();
    }
    // 현재 체력 값 설정
    target.SetHealth(newHealth);
    // 아이템 수량 감소
    Amount--;
    std::cout << target.GetName() << "가 " << Name << "을 사용했습니다. "
        << target.GetName() << " 체력: " << target.GetHealth() << endl;
}
