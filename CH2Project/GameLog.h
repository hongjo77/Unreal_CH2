#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>

class GameLog
{
public:
    static GameLog* instance;
    std::unordered_map<std::string, bool> achievements;
    std::vector<std::string> logs;
    std::unordered_map<std::string, int> statistics;

    void CheckAchievement(const std::string& achievementName);
    void AddLog(const std::string& logEntry);
    void UpdateStat(const std::string& statName, int value);
    bool IsAchieved(const std::string& achievementName);
    void PrintLogs();
    void PrintStatistics();
    void KillAchievement(const std::string& monsterName);
    void GoldAchievement(int amount);
    void TakeDamageAchievement(int amount);
    void AttackDamageAchievement(int amount);
    void LevelAchievement(int level);
};