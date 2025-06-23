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
	cout << Name << " óġ!" << endl;

	// ���� �������� �� ��� ���
	int goldReward = 100 + rand() % 100;
	// �÷��̾� ����ġ + 50 exp
	player.SetExperience(player.GetExperience() + 50);
	// �÷��̾� ��� + 100~200 ��� + ��ģ ��
	player.SetGold(player.GetGold() + goldReward + StolenMoney);
	cout << player.GetName() << "�� 50 EXP�� " << goldReward << " ��带 ȹ���߽��ϴ�. ���� EXP: "
		<< player.GetExperience() << "/100, ���: " << player.GetGold() << endl;

	// 30% Ȯ���� ������ ���
	int dropChance = rand() % 100;
	if (dropChance < 30)
	{
		Item* droppedItem = DropItem();
		if (droppedItem)
		{
			player.GetInventory().push_back(droppedItem);
			cout << droppedItem->GetName() << " �������� ȹ���߽��ϴ�!" << endl;
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
	cout << Name << "�� " << player.GetName() << "�� �����մϴ�! "
		<< player.GetName() << " ü��: " << prevPlayerHealth << " �� " << player.GetHealth();
	if (prevGold > 0) 
	{
		cout << " ���: " << prevGold << " -> " << player.GetGold() << endl;
	}
	else 
	{
		cout << " ���: "<< player.GetGold() << endl;
	}
	cout << endl;
}
