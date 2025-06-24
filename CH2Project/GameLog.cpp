#include "GameLog.h"

GameLog* GameLog::instance = nullptr;

void GameLog::CheckAchievement(const std::string& achievementName)
{
    std::string msg = "[*** 업적 달성 ***] : " + achievementName;
    std::cout << msg << std::endl;
    logs.push_back(msg);
    achievements[achievementName] = true;
}

void GameLog::AddLog(const std::string& logEntry)
{
    logs.push_back(logEntry);
}

void GameLog::UpdateStat(const std::string& statName, int value)
{
    statistics[statName] += value;
}

bool GameLog::IsAchieved(const std::string& achievementName)
{
    return achievements.find(achievementName) != achievements.end() && achievements[achievementName];
}

void GameLog::PrintLogs()
{
    system("cls");
    std::cout << "=== 게임 로그 ===" << std::endl;
    for (const auto& log : logs)
    {
        std::cout << log << std::endl;
    }
}

void GameLog::PrintStatistics()
{
    system("cls");
    std::cout << "=== 통계 ===" << std::endl;
    for (const auto& stat : statistics)
    {
        std::cout << stat.first << ": " << stat.second << std::endl;
    }
}

void GameLog::PrintAchievement()
{
	system("cls");
    std::cout << "=== 업적 목록 ===" << std::endl;
    for (const auto& ach : achievements)
    {
        std::cout << "[*** 업적 달성 ***] : " << ach.first << std::endl;
    }
}

void GameLog::KillAchievement(const std::string& monsterName)
{
    statistics[monsterName + "_killed"]++;
    logs.push_back("Player killed a " + monsterName + ".");

    if (monsterName == "Goblin" && statistics["Goblin_killed"] == 5)
    {
        if (!IsAchieved("고블린 5마리 처치"))
        {
            CheckAchievement("고블린 5마리 처치");
        }
    }
	if (monsterName == "Orc" && statistics["Orc_killed"] == 5)
    {
        if (!IsAchieved("오크 5마리 처치"))
        {
            CheckAchievement("오크 5마리 처치");
        }
    }
	if (monsterName == "Troll" && statistics["Troll_killed"] == 5)
    {
        if (!IsAchieved("트롤 5마리 처치"))
        {
            CheckAchievement("트롤 5마리 처치");
        }
    }
	if (monsterName == "Golden Goblin" && statistics["Golden Goblin_killed"] == 5)
    {
        if (!IsAchieved("황금 고블린 5마리 처치"))
        {
            CheckAchievement("황금 고블린 5마리 처치");
        }
    }
}

void GameLog::GoldAchievement(int amount)
{
    if (amount > 0)
    {
        statistics["Gold_Gained"] += amount;
        logs.push_back("Player gained " + std::to_string(amount) + " gold.");

        if (statistics["Gold_Gained"] >= 500 && !IsAchieved("500 골드 획득"))
        {
            CheckAchievement("500 골드 획득");
        }
    }
    else if (amount < 0)
    {
        statistics["Gold_Spent"] += -amount;
        logs.push_back("Player spent " + std::to_string(-amount) + " gold.");

        if (statistics["Gold_Spent"] >= 500 && !IsAchieved("500 골드 사용"))
        {
            CheckAchievement("500 골드 사용");
        }
    }
}

void GameLog::TakeDamageAchievement(int amount)
{
    statistics["Damage_Taken"] += amount;
    logs.push_back("Player took " + std::to_string(amount) + " damage.");

    if (statistics["Damage_Taken"] >= 1000 && !IsAchieved("받은 데미지 1000 누적"))
    {
        CheckAchievement("받은 데미지 1000 누적");
    }
}

void GameLog::AttackDamageAchievement(int amount)
{
    statistics["Damage_Attack"] += amount;
    logs.push_back("Player attack " + std::to_string(amount) + " damage.");

    if (statistics["Damage_Attack"] >= 1000 && !IsAchieved("준 데미지 1000 누적"))
    {
        CheckAchievement("준 데미지 1000 누적");
    }
}

void GameLog::LevelAchievement(int level)
{
    logs.push_back("Player level up to " + std::to_string(level));
    if (level >= 10 && !IsAchieved("레벨 10 달성"))
    {
        CheckAchievement("레벨 10 달성");
    }
}

void GameLog::EquipmentAchievement(const std::string& equipmentName, int level, int result)
{
    statistics[equipmentName + "_level"]=level;

	if(result==0)
	{
		logs.push_back(equipmentName + " upgrade successful.");
		statistics["upgrade success"]++;
	}
	else if(result==1)
	{
		logs.push_back(equipmentName + " upgrade failed.");
		statistics["upgrade fail"]++;
	}
	else
	{
		logs.push_back(equipmentName + " downgrade.");
		statistics["downgrade"]++;
	}
    

    if (statistics[equipmentName + "_level"] >= 5 && !IsAchieved(equipmentName+"_5강"))
    {
        CheckAchievement(equipmentName+"_5강");
    }
	if (statistics["upgrade success"] >= 10 && !IsAchieved("강화 성공 10번 달성"))
    {
        CheckAchievement("강화 성공 10번 달성");
    }
	else if (statistics["upgrade fail"] >= 10 && !IsAchieved("강화 실패 10번 달성"))
    {
        CheckAchievement("강화 실패 10번 달성");
    }
	if (statistics["downgrade"] >= 10 && !IsAchieved("강화 하락 10번 달성"))
    {
        CheckAchievement("강화 하락 10번 달성");
    }
}
