#include "BossMonster.h"
#include "GameLog.h"
#include <iostream>
#include <sstream>

BossMonster::BossMonster(int level)
    : Monster(
        "Elder Dragon",
        (rand() % (level * 50)) + (level * 200),
        (rand() % (level * 10)) + (level * 20)
    ), SkillAttack(rand() % (level * 10) + (level*50)),
rng(chrono::high_resolution_clock::now().time_since_epoch().count()),
chanceDistribution(0,99){}

// 보스인지 아닌지 확인
bool BossMonster::IsBoss() const { return true; }

void BossMonster::TextArt() const {
    string textart = R"(
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣤⣤⣤⣤⡼⠀⢀⡀⣀⢱⡄⡀⠀⠀⠀⢲⣤⣤⣤⣤⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣴⣾⣿⣿⣿⣿⣿⡿⠛⠋⠁⣤⣿⣿⣿⣧⣷⠀⠀⠘⠉⠛⢻⣷⣿⣽⣿⣿⣷⣦⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⢀⣴⣞⣽⣿⣿⣿⣿⣿⣿⣿⠁⠀⠀⠠⣿⣿⡟⢻⣿⣿⣇⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣟⢦⡀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⣠⣿⡾⣿⣿⣿⣿⣿⠿⣻⣿⣿⡀⠀⠀⠀⢻⣿⣷⡀⠻⣧⣿⠆⠀⠀⠀⠀⣿⣿⣿⡻⣿⣿⣿⣿⣿⠿⣽⣦⡀⠀⠀⠀⠀
⠀⠀⠀⠀⣼⠟⣩⣾⣿⣿⣿⢟⣵⣾⣿⣿⣿⣧⠀⠀⠀⠈⠿⣿⣿⣷⣈⠁⠀⠀⠀⠀⣰⣿⣿⣿⣿⣮⣟⢯⣿⣿⣷⣬⡻⣷⡄⠀⠀⠀
⠀⠀⢀⡜⣡⣾⣿⢿⣿⣿⣿⣿⣿⢟⣵⣿⣿⣿⣷⣄⠀⣰⣿⣿⣿⣿⣿⣷⣄⠀⢀⣼⣿⣿⣿⣷⡹⣿⣿⣿⣿⣿⣿⢿⣿⣮⡳⡄⠀⠀
⠀⢠⢟⣿⡿⠋⣠⣾⢿⣿⣿⠟⢃⣾⢟⣿⢿⣿⣿⣿⣾⡿⠟⠻⣿⣻⣿⣏⠻⣿⣾⣿⣿⣿⣿⡛⣿⡌⠻⣿⣿⡿⣿⣦⡙⢿⣿⡝⣆⠀
⠀⢯⣿⠏⣠⠞⠋⠀⣠⡿⠋⢀⣿⠁⢸⡏⣿⠿⣿⣿⠃⢠⣴⣾⣿⣿⣿⡟⠀⠘⢹⣿⠟⣿⣾⣷⠈⣿⡄⠘⢿⣦⠀⠈⠻⣆⠙⣿⣜⠆
⢀⣿⠃⡴⠃⢀⡠⠞⠋⠀⠀⠼⠋⠀⠸⡇⠻⠀⠈⠃⠀⣧⢋⣼⣿⣿⣿⣷⣆⠀⠈⠁⠀⠟⠁⡟⠀⠈⠻⠀⠀⠉⠳⢦⡀⠈⢣⠈⢿⡄
⣸⠇⢠⣷⠞⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠻⠿⠿⠋⠀⢻⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⢾⣆⠈⣷
⡟⠀⡿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣴⣶⣤⡀⢸⣿⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⡄⢹
⡇⠀⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⠀⠈⣿⣼⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠃⢸
⢡⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠻⠶⣶⡟⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡼
⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡾⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡁⢠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⣿⣼⣀⣠⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
)";
    cout << textart << endl;
}

void BossMonster::OnDeath(Characters& player) 
{
    cout << endl;
	std::stringstream oss;
    oss << Name << GREEN << " 처치!" << RESET << endl;
	GameLog::GetInstance()->PrintAndLog(oss.str());
    oss.str("");
	oss.clear();
	oss << GREEN << "축하합니다! 보스 " << Name << "을(를) 처치하고 게임을 클리어했습니다!" << RESET << endl;
	GameLog::GetInstance()->PrintAndLog(oss.str());
}

void BossMonster::AttackPlayer(Characters& player) 
{
	std::stringstream oss;
    int prevPlayerHealth = player.GetHealth();
    bool IsSkill = false; //스킬 사용 여부
    int newHealth = 0;
    int ArmorSubAttack = 0;

    //30% 확률로 스킬 공격
    int skillChance = chanceDistribution(rng);
    if (skillChance < 30)
    {
        oss << Name << "이(가) 강력한 기술로 " << player.GetName() << "를 공격합니다! ";
		GameLog::GetInstance()->PrintAndLog(oss.str());
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
        oss << Name << "이(가) " << player.GetName() << "를 공격합니다! ";
		GameLog::GetInstance()->PrintAndLog(oss.str());
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

	oss.str("");
	oss.clear();
    oss << player.GetName() << " 체력: " << GREEN << prevPlayerHealth << RESET << " → " << RED << player.GetHealth() << RESET << endl;
	GameLog::GetInstance()->PrintAndLog(oss.str());

    // 일반 공격 시 각각 20% 확률로 공격력 감소, 방어력 감소 디버프
    if (!IsSkill)
    {
        int debuffChance = chanceDistribution(rng);
        if (debuffChance >= 0 && debuffChance < 20)
        {
            int prevPlayerAttack = player.GetBaseAttack();
            int DroppedPlayerAttack = static_cast<int>(player.GetBaseAttack() * 0.8);
            player.SetAttack(DroppedPlayerAttack);

			oss.str("");
			oss.clear();
            oss << player.GetName() << "이(가) 공격력 감소 디버프에 걸렸습니다! "
                << player.GetName() << " 공격력: " << GREEN << prevPlayerAttack << RESET << " → " << RED << player.GetBaseAttack() << RESET << endl;
			GameLog::GetInstance()->PrintAndLog(oss.str());
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
			oss.str("");
			oss.clear();
            oss << player.GetName() << "이(가) 방어력 감소 디버프에 걸렸습니다! "
                << player.GetName() << " 방어력: " << GREEN << prevPlayerArmorStat << RESET << " → " << RED << player.GetTotalArmorStat() << RESET << endl;
			GameLog::GetInstance()->PrintAndLog(oss.str());
		}
    }
    cout << endl;
	// 로그 추가
	GameLog::GetInstance()->TakeDamageAchievement(-ArmorSubAttack);
}
