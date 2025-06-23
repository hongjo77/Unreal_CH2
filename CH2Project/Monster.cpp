#include "Monster.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include <iostream>


Monster::Monster(const string& name, int health, int attack)
    : Name(name), Health(health), Attack(attack) {}

Monster::~Monster() {}

// 멤버 변수 Getter
string Monster::GetName() const { return Name; }
int Monster::GetHealth() const { return Health; }
int Monster::GetAttack() const { return Attack; }

// 피격
void Monster::TakeDamage(int damage)
{
    Health -= damage;
    if (Health < 0)
    {
        Health = 0;
    }
}

void Monster::OnDeath(Characters& player) {
    cout << endl;
    cout << Name << " 처치!" << endl;

    // 적을 물리쳤을 때 얻는 골드
    int goldReward = 10 + rand() % 11;
    // 플레이어 경험치 + 50 exp
    player.SetExperience(player.GetExperience() + 50);
    // 플레이어 골드 + 10~20 골드
    player.SetGold(player.GetGold() + goldReward);
    cout << player.GetName() << "가 50 EXP와 " << goldReward << " 골드를 획득했습니다. 현재 EXP: " 
        << player.GetExperience() << "/100, 골드: " << player.GetGold() << endl;

    // 30% 확률로 아이템 드랍
    int dropChance = rand() % 100;
    if (dropChance < 30)
    {
        Item* droppedItem = DropItem();
        if (droppedItem)
        {
            player.GetInventory().push_back(droppedItem);
            cout << droppedItem->GetName() << " 아이템을 획득했습니다!" << endl;
        }
    }
}

// 몬스터가 아이템을 드랍
Item* Monster::DropItem() 
{
    int itemType = rand() % 2;
    Item* dropped = nullptr;
    if (itemType == 0)
    {
        dropped = new HealthPotion();
        cout << Name << "이(가) 체력 포션을 드랍했습니다!" << endl;
    }
    else
    {
        dropped = new AttackBoost();
        cout << Name << "이(가) 공격력 부스트를 드랍했습니다!" << endl;
    }
    return dropped;
}

void Monster::AttackPlayer(Characters& player) {
    int prevPlayerHealth = player.GetHealth();
    int newHealth = prevPlayerHealth - Attack;

    if (newHealth < 0) { newHealth = 0; }
    player.SetHealth(newHealth);
    cout << Name << "이 " << player.GetName() << "를 공격합니다! "
        << player.GetName() << " 체력: " << prevPlayerHealth << " → " << player.GetHealth() << endl;
    cout << endl;
}

// 기본적으로 모든 적은 보스, 특수 몬스터가 아님
bool Monster::IsBoss() const { return false; }
bool Monster::IsGoldenGoblin() const { return false; }
