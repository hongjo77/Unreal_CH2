#include "BossMonster.h"
#include "GameLog.h"
#include <iostream>

BossMonster::BossMonster(int level)
    : Monster(
        "Orc Shaman",
        (rand() % (level * 50)) + (level * 200),
        (rand() % (level * 10)) + (level * 20)
    ), SkillAttack(rand() % (level * 10) + (level*50)),
rng(chrono::high_resolution_clock::now().time_since_epoch().count()),
chanceDistribution(0,99){}

// 보스인지 아닌지 확인
bool BossMonster::IsBoss() const { return true; }

void BossMonster::OnDeath(Characters& player) 
{
    cout << endl;
    cout << COLOR_GREEN << Name << " 처치!" << COLOR_RESET << endl;
    cout << COLOR_GREEN << "축하합니다! 보스 " << Name << "을(를) 처치하고 게임을 클리어했습니다!" << COLOR_RESET << endl;
}

void BossMonster::AttackPlayer(Characters& player) 
{
    int prevPlayerHealth = player.GetHealth();
    bool IsSkill = false; //스킬 사용 여부
    int newHealth = 0;
    int ArmorSubAttack = 0;

    //30% 확률로 스킬 공격
    int skillChance = chanceDistribution(rng);
    if (skillChance < 30)
    {
        cout << COLOR_RED << Name << "이(가) 강력한 기술로 " << player.GetName() << "를 공격합니다! " << COLOR_RESET;
        IsSkill = true;
        if (player.GetTotalArmorStat() - SkillAttack > 0) {
            ArmorSubAttack = 0;
        }
        else {
            ArmorSubAttack = player.GetTotalArmorStat() - SkillAttack;
        }
        newHealth = prevPlayerHealth + ArmorSubAttack;
    }
    else
    {
        cout << COLOR_RED << Name << "이(가) " << player.GetName() << "를 공격합니다! "<< COLOR_RESET;
        if (player.GetTotalArmorStat() - Attack > 0) {
            ArmorSubAttack = 0;
        }
        else {
            ArmorSubAttack = player.GetTotalArmorStat() - Attack;
        }
        newHealth = prevPlayerHealth + ArmorSubAttack;
    }

    if (newHealth < 0)
    {
        newHealth = 0;
    }
    player.SetHealth(newHealth);

    cout<< COLOR_RED << player.GetName() << " 체력: " << prevPlayerHealth << " → " << player.GetHealth() << COLOR_RESET << endl;

    // 일반 공격 시 각각 20% 확률로 공격력 감소, 방어력 감소 디버프
    if (!IsSkill)
    {
        int debuffChance = chanceDistribution(rng);
        if (debuffChance >= 0 && debuffChance < 20)
        {
            int prevPlayerAttack = player.GetBaseAttack();
            int DroppedPlayerAttack = static_cast<int>(player.GetBaseAttack() * 0.8);
            player.SetAttack(DroppedPlayerAttack);

            cout << COLOR_RED << player.GetName() << "이(가) 공격력 감소 디버프에 걸렸습니다! "
                << player.GetName() << " 공격력: " << prevPlayerAttack << " → " << player.GetBaseAttack() << COLOR_RESET << endl;
        }
        else if(debuffChance >=20 && debuffChance < 40)
        {
            int prevPlayerArmorStat = player.GetTotalArmorStat();
            auto EquipList = player.GetEquipments();
            for (auto& equip : EquipList) {
                if (equip->GetStat() > 0) {
                    equip->SetStat(equip->GetStat() - 5);
                }
                else {
                    equip->SetStat(0);
                }
            }
            cout << COLOR_RED << player.GetName() << "이(가) 방어력 감소 디버프에 걸렸습니다! "
                << player.GetName() << "방어력: " << prevPlayerArmorStat << " → " << player.GetTotalArmorStat() << COLOR_RESET << endl;
        }
    }
    cout << endl;
	// 로그 추가
	GameLog::GetInstance()->TakeDamageAchievement(-ArmorSubAttack);
}
