#include "Monster.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include "GameLog.h"
#include <iostream>
#include <sstream>


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
	// 로그 추가
	GameLog::GetInstance()->AttackDamageAchievement(damage);
}

void Monster::OnDeath(Characters& player) {
	std:stringstream oss;
    cout << endl;
    oss << Name << GREEN << " 처치!" << RESET << endl;
	GameLog::GetInstance()->PrintAndLog(oss.str());


    // 적을 물리쳤을 때 얻는 골드
    int goldReward = 10 + rand() % 11;
    // 플레이어 경험치 + 50 exp
    player.SetExperience(player.GetExperience() + 50);
    // 플레이어 골드 + 10~20 골드
    player.SetGold(player.GetGold() + goldReward);
	oss.str("");
	oss.clear();
    oss << player.GetName() << "가"<<GREEN<<"50 EXP"<<RESET <<"와 " <<GREEN << goldReward << " 골드"<<RESET<<"를 획득했습니다.현재 EXP : " 
        << player.GetExperience() << "/100, 골드: " << player.GetGold() << endl;
	GameLog::GetInstance()->PrintAndLog(oss.str());

    // 30% 확률로 아이템 드랍
    int dropChance = rand() % 100;
    if (dropChance < 30)
    {
        int index = DropItem();
        auto& playerInventory = player.GetInventory();
        playerInventory[index]->SetAmount(playerInventory[index]->GetAmount() + 1);
        oss.str("");
		oss.clear();
		oss << player.GetName() << "이(가) " << GREEN << playerInventory[index]->GetName() << RESET <<"을(를) 1개 획득했습니다!" << endl;
		GameLog::GetInstance()->PrintAndLog(oss.str());
	}
	// 로그 추가
	GameLog::GetInstance()->TakeDamageAchievement(goldReward);
}

// 몬스터가 아이템을 드랍
int Monster::DropItem() 
{
	std::stringstream oss;
    int itemType = rand() % 2;
    if (itemType == 0)
    {
        oss <<  Name << "이(가)" <<GREEN<< " Health Potion" <<RESET <<"을(를) 드랍했습니다!" <<  endl;
		GameLog::GetInstance()->PrintAndLog(oss.str());
	}
    else
    {
        oss <<  Name << "이(가)" <<GREEN<<" Attack Boost" <<RESET<<"을(를) 드랍했습니다!" <<  endl;
		GameLog::GetInstance()->PrintAndLog(oss.str());
	}
    return itemType;
}

void Monster::AttackPlayer(Characters& player) {
	std:stringstream oss;
    int prevPlayerHealth = player.GetHealth();
    int ArmorSubAttack = 0;
    if (player.GetTotalArmorStat() - Attack > 0) {
        ArmorSubAttack = 0;
    }
    else {
        ArmorSubAttack = player.GetTotalArmorStat() - Attack;
    }
    int newHealth = prevPlayerHealth + ArmorSubAttack;

    if (newHealth < 0) { newHealth = 0; }
    player.SetHealth(newHealth);
    oss << Name << "이(가) " << player.GetName() << "를 공격합니다! "
        << player.GetName() << " 체력: " << GREEN << prevPlayerHealth << RESET << " → " << RED<< player.GetHealth() << RESET << endl;
    GameLog::GetInstance()->PrintAndLog(oss.str());
	cout << endl;
	// 로그 추가
	GameLog::GetInstance()->TakeDamageAchievement(-ArmorSubAttack);
}

// 기본적으로 모든 적은 보스, 특수 몬스터가 아님
bool Monster::IsBoss() const { return false; }
bool Monster::IsGoldenGoblin() const { return false; }
