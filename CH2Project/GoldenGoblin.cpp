#include "GoldenGoblin.h"
#include "GameLog.h"
#include <iostream>

GoldenGoblin::GoldenGoblin(int level)
	:Monster(
		"Golden Goblin",
		(rand()%(level*50))+(level*50),
		(rand() % (level * 6)) + (level * 5)
	),GoldAttack((rand()%(level*10))+(level*10)){}

bool GoldenGoblin::IsGoldenGoblin() const { return true; }

void GoldenGoblin::OnDeath(Characters& player) 
{
	cout << endl;
	cout << Name << " 처치!" << endl;

	// 적을 물리쳤을 때 얻는 골드 (훔친 돈 포함)
	int goldReward = (100 + rand() % 100) + StolenMoney;
	// 플레이어 경험치 + 50 exp
	player.SetExperience(player.GetExperience() + 50);
	// 플레이어 골드 + 100~200 골드 + 훔친 돈
	player.SetGold(player.GetGold() + goldReward);
	cout << player.GetName() << "가 50 EXP와 " << goldReward << " 골드를 획득했습니다. 현재 EXP: "
		<< player.GetExperience() << "/100, 골드: " << player.GetGold() << endl;

	// 30% 확률로 아이템 드랍
	int dropChance = rand() % 100;
	if (dropChance < 30)
	{
		int index = DropItem();
		auto& playerInventory = player.GetInventory();
		playerInventory[index]->SetAmount(playerInventory[index]->GetAmount() + 1);
		cout << player.GetName() << "이(가) " << playerInventory[index]->GetName() << "을(를) 1개 획득했습니다!" << endl;
	}
	// 로그 추가
	GameLog::instance->GoldAchievement(goldReward);
}

void GoldenGoblin::AttackPlayer(Characters& player) 
{
	int prevPlayerHealth = player.GetHealth();
	int ArmorSubAttack = 0;
	if (player.GetTotalArmorStat() - Attack > 0) {
		ArmorSubAttack = 0;
	}
	else {
		ArmorSubAttack = player.GetTotalArmorStat() - Attack;
	}
	int newHealth = prevPlayerHealth + ArmorSubAttack;
	int prevGold = player.GetGold();
	if (prevGold > 0) 
	{
		int newGold = prevGold - GoldAttack;
		StolenMoney += GoldAttack;
		if (newGold < 0) { newGold = 0; }
		player.SetGold(newGold);
	}

	if (newHealth < 0) { newHealth = 0; }
	player.SetHealth(newHealth);
	cout << Name << "이(가) " << player.GetName() << "를 공격합니다! "
		<< player.GetName() << " 체력: " << prevPlayerHealth << " → " << player.GetHealth();
	if (prevGold > 0) 
	{
		cout << " 골드: " << prevGold << " -> " << player.GetGold() << endl;
	}
	else 
	{
		cout << " 골드: "<< player.GetGold() << endl;
	}
	cout << endl;
	// 로그 추가
	GameLog::instance->TakeDamageAchievement(-ArmorSubAttack);
}
