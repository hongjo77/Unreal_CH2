﻿#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>

class GameLog
{
private:
	static GameLog* instance;
	std::unordered_map<std::string, bool> achievements;
    std::vector<std::string> logs;
    std::unordered_map<std::string, int> statistics;

	GameLog() = default;

public:
    static GameLog* GetInstance();

    void CheckAchievement(const std::string& achievementName);
    void AddLog(const std::string& logEntry);
	void PrintAndLog(const std::string& msg);
    void UpdateStat(const std::string& statName, int value);
    bool IsAchieved(const std::string& achievementName);
    void PrintLogs();
    void PrintStatistics();
	void PrintAchievement();
    void KillAchievement(const std::string& monsterName);
    void GoldAchievement(int amount);
    void TakeDamageAchievement(int amount);
    void AttackDamageAchievement(int amount);
    void LevelAchievement(int level);
	void EquipmentAchievement(const std::string& equipmentName, int level, int result);
};