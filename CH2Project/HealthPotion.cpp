#include "HealthPotion.h"
#include "Characters.h"
#include <iostream>

//체력포션 생성자 Name : Health Potion
HealthPotion::HealthPotion() : Item("Health Potion") {}

void HealthPotion::Use(Characters& target)
{
    // 50만큼 회복
    int newHealth = target.GetHealth() + 50;
    // 초과 회복시 최대 체력으로 설정
    if (newHealth > target.GetMaxHealth())
    {
        newHealth = target.GetMaxHealth();
    }
    target.SetHealth(newHealth);
    cout << target.GetName() << "가 " << Name << "을 사용했습니다. "
        << target.GetName() << " 체력: " << target.GetHealth() << endl;
}
