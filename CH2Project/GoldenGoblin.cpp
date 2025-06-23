#include "GoldenGoblin.h"
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
	cout << Name << " Ã³Ä¡!" << endl;

	// ÀûÀ» ¹°¸®ÃÆÀ» ¶§ ¾ò´Â °ñµå
	int goldReward = 100 + rand() % 100;
	// ÇÃ·¹ÀÌ¾î °æÇèÄ¡ + 50 exp
	player.SetExperience(player.GetExperience() + 50);
	// ÇÃ·¹ÀÌ¾î °ñµå + 100~200 °ñµå + ÈÉÄ£ µ·
	player.SetGold(player.GetGold() + goldReward + StolenMoney);
	cout << player.GetName() << "°¡ 50 EXP¿Í " << goldReward << " °ñµå¸¦ È¹µæÇß½À´Ï´Ù. ÇöÀç EXP: "
		<< player.GetExperience() << "/100, °ñµå: " << player.GetGold() << endl;

	// 30% È®·ü·Î ¾ÆÀÌÅÛ µå¶ø
	int dropChance = rand() % 100;
	if (dropChance < 30)
	{
		Item* droppedItem = DropItem();
		if (droppedItem)
		{
			player.GetInventory().push_back(droppedItem);
			cout << droppedItem->GetName() << " ¾ÆÀÌÅÛÀ» È¹µæÇß½À´Ï´Ù!" << endl;
		}
	}
}

void GoldenGoblin::AttackPlayer(Characters& player) 
{
	int prevPlayerHealth = player.GetHealth();
	int newHealth = prevPlayerHealth - Attack;
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
	cout << Name << "ÀÌ " << player.GetName() << "¸¦ °ø°ÝÇÕ´Ï´Ù! "
		<< player.GetName() << " Ã¼·Â: " << prevPlayerHealth << " ¡æ " << player.GetHealth();
	if (prevGold > 0) 
	{
		cout << " °ñµå: " << prevGold << " -> " << player.GetGold() << endl;
	}
	else 
	{
		cout << " °ñµå: "<< player.GetGold() << endl;
	}
	cout << endl;
}
