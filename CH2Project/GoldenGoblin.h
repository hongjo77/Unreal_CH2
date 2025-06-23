#pragma once
#include "Monster.h"

using namespace std;

class GoldenGoblin : public Monster 
{
public:
	GoldenGoblin(int level);
	bool IsGoldenGoblin() const override;
	void OnDeath(Characters& player) override;
	void AttackPlayer(Characters& player) override;

private:
	int GoldAttack;
	int StolenMoney = 0;
};