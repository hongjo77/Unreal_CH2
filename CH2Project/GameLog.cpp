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

void GameLog::KillAchievement(const std::string& monsterName)
{
    statistics[monsterName + "_killed"]++;
    logs.push_back("Player killed a " + monsterName + ".");

    if (monsterName == "Goblin" && statistics["Goblin_killed"] == 3)
    {
        if (!IsAchieved("고블린 3마리 처치"))
        {
            CheckAchievement("고블린 3마리 처치");
        }
    }
}

void GameLog::GoldAchievement(int amount)
{
    if (amount > 0)
    {
        statistics["Gold_Gained"] += amount;
        logs.push_back("Player gained " + std::to_string(amount) + " gold.");

        if (statistics["Gold_Gained"] >= 100 && !IsAchieved("100 골드 획득"))
        {
            CheckAchievement("100 골드 획득");
        }
    }
    else if (amount < 0)
    {
        statistics["Gold_Spent"] += -amount;
        logs.push_back("Player spent " + std::to_string(-amount) + " gold.");

        if (statistics["Gold_Spent"] >= 100 && !IsAchieved("100 골드 사용"))
        {
            CheckAchievement("100 골드 사용");
        }
    }
}

void GameLog::TakeDamageAchievement(int amount)
{
    statistics["Damage_Taken"] += amount;
    logs.push_back("Player took " + std::to_string(amount) + " damage.");

    if (statistics["Damage_Taken"] >= 100 && !IsAchieved("받은 데미지 100 누적"))
    {
        CheckAchievement("받은 데미지 100 누적");
    }
}

void GameLog::AttackDamageAchievement(int amount)
{
    statistics["Damage_Attack"] += amount;
    logs.push_back("Player attack " + std::to_string(amount) + " damage.");

    if (statistics["Damage_Attack"] >= 100 && !IsAchieved("준 데미지 100 누적"))
    {
        CheckAchievement("준 데미지 100 누적");
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
