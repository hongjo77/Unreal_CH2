#include "GameLog.h"
#include "Color.h"

GameLog* GameLog::instance = nullptr;

GameLog* GameLog::GetInstance()
{
	if(!instance)
	{
		instance = new GameLog();
	}
	return instance;
}

void GameLog::CheckAchievement(const std::string& achievementName)
{
    std::string msg = std::string(YELLOW)+"[*** 업적 달성 ***] : " + achievementName + RESET;
    std::cout << msg << std::endl;
    logs.push_back(msg);
    achievements[achievementName] = true;
}

void GameLog::AddLog(const std::string& logEntry)
{
    logs.push_back(logEntry);
}

void GameLog::PrintAndLog(const std::string& msg)
{
    std::cout << msg;
	AddLog(msg);
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
    std::cout << GREEN << "=== 게임 로그 ===" << RESET << std::endl;
    for (const auto& log : logs)
    {
        std::cout << log << std::endl;
    }
}

void GameLog::PrintStatistics()
{
    system("cls");

    const int boxWidth = 44; // 박스의 고정 너비
    std::vector<std::pair<std::string, int>> statList;
    for (const auto& stat : statistics)
    {
        statList.push_back(stat);
    }

    // 박스 상단
    std::cout << GREEN << "┌";
    for (int i = 0; i < boxWidth; i++)
    {
        std::cout << "─";
    }
    std::cout << "┐" << RESET << std::endl;

    // 타이틀
    std::string title = "★ 통계 ★";
    int title_display_len = 0;
    for (size_t i = 0; i < title.size(); )
    {
        unsigned char c = title[i];
        if ((c & 0x80) == 0)
        {
            ++title_display_len;
            i++;
        }
        else if ((c & 0xE0) == 0xC0)
        {
            ++title_display_len;
            i += 2;
        }
        else if ((c & 0xF0) == 0xE0)
        {
            title_display_len += 2;
            i += 3;
        }
        else if ((c & 0xF8) == 0xF0)
        {
            ++title_display_len;
            i += 4;
        }
        else
        {
            i++;
        }
    }
    int leftPad = (boxWidth - title_display_len) / 2;
    int rightPad = boxWidth - title_display_len - leftPad;
    std::cout << GREEN << "│" << RESET
              << std::string(leftPad, ' ') << title << std::string(rightPad, ' ')
              << GREEN << "│" << RESET << std::endl;

    // 중간 구분선
    std::cout << GREEN << "├";
    for (int i = 0; i < boxWidth; i++)
    {
        std::cout << "─";
    }
    std::cout << "┤" << RESET << std::endl;

    // 통계 내용
    if (statList.empty())
    {
        std::string emptyMsg = "기록된 통계가 없습니다";
        int pad = boxWidth - emptyMsg.length();
        std::cout << GREEN << "│" << RESET << " " << YELLOW << emptyMsg << RESET << std::string(pad - 1, ' ') << GREEN << "│" << RESET << std::endl;
    }
    else
    {
        for (const auto& stat : statList)
        {
            std::string statMsg = stat.first + ": " + std::to_string(stat.second);

            // 출력 너비 계산 (한글 2칸, 영문/숫자/기호 1칸)
            int display_len = 0;
            for (size_t i = 0; i < statMsg.size(); )
            {
                unsigned char c = statMsg[i];
                if ((c & 0x80) == 0)
                {
                    ++display_len;
                    i++;
                }
                else if ((c & 0xE0) == 0xC0)
                {
                    ++display_len;
                    i += 2;
                }
                else if ((c & 0xF0) == 0xE0)
                {
                    display_len += 2;
                    i += 3;
                }
                else if ((c & 0xF8) == 0xF0)
                {
                    ++display_len;
                    i += 4;
                }
                else
                {
                    i++;
                }
            }
            int pad = boxWidth - 2 - display_len;
            std::cout << GREEN << "│" << RESET << " " << YELLOW << stat.first << RESET << ": " << stat.second
                      << std::string(pad, ' ') << GREEN << " │" << RESET << std::endl;
        }
    }

    // 박스 하단
    std::cout << GREEN << "└";
    for (int i = 0; i < boxWidth; i++)
    {
        std::cout << "─";
    }
    std::cout << "┘" << RESET << std::endl;
}

void GameLog::PrintAchievement()
{
	system("cls");

    const int boxWidth = 44; // 박스의 고정 너비
    std::vector<std::string> achList;
    for (const auto& ach : achievements)
    {
        achList.push_back("[업적 달성] : " + ach.first);
    }

    // 박스 상단
    std::cout << GREEN << "┌";
    for (int i = 0; i < boxWidth; i++)
    {
        std::cout << "─";
    }
    std::cout << "┐" << RESET << std::endl;

    // 타이틀
    std::string title = "★ 업적 목록 ★";
    int title_display_len = 0;
    for (size_t i = 0; i < title.size(); )
    {
        unsigned char c = title[i];
        if ((c & 0x80) == 0)
        {
            ++title_display_len;
            i++;
        }
        else if ((c & 0xE0) == 0xC0)
        {
            ++title_display_len;
            i += 2;
        }
        else if ((c & 0xF0) == 0xE0)
        {
            title_display_len += 2;
            i += 3;
        }
        else if ((c & 0xF8) == 0xF0)
        {
            ++title_display_len;
            i += 4;
        }
        else
        {
            i++;
        }
    }
    int leftPad = (boxWidth - title_display_len) / 2;
    int rightPad = boxWidth - title_display_len - leftPad;
    std::cout << GREEN << "│" << RESET
              << std::string(leftPad, ' ') << title << std::string(rightPad, ' ')
              << GREEN << "│" << RESET << std::endl;

    // 중간 구분선
    std::cout << GREEN << "├";
    for (int i = 0; i < boxWidth; i++)
    {
        std::cout << "─";
    }
    std::cout << "┤" << RESET << std::endl;

    // 업적 내용
    if (achList.empty())
    {
        std::string emptyMsg = "달성한 업적이 없습니다";
        int pad = boxWidth - emptyMsg.length();
        std::cout << GREEN << "│" << RESET << " " << YELLOW << emptyMsg << RESET << std::string(pad - 1, ' ') << GREEN << "│" << RESET << std::endl;
    }
    else
    {
        for (const auto& msg : achList)
        {
            // 출력 너비 계산 (한글 2칸, 영문/숫자/기호 1칸)
            int display_len = 0;
            for (size_t i = 0; i < msg.size(); )
            {
                unsigned char c = msg[i];
                if ((c & 0x80) == 0)
                {
                    ++display_len;
                    i++;
                }
                else if ((c & 0xE0) == 0xC0)
                {
                    ++display_len;
                    i += 2;
                }
                else if ((c & 0xF0) == 0xE0)
                {
                    display_len += 2;
                    i += 3;
                }
                else if ((c & 0xF8) == 0xF0)
                {
                    ++display_len;
                    i += 4;
                }
                else
                {
                    i++;
                }
            }
            int pad = boxWidth - 2 - display_len;
            std::cout << GREEN << "│" << RESET << " " << YELLOW << msg << RESET
                      << std::string(pad, ' ') << GREEN << " │" << RESET << std::endl;
        }
    }

    // 박스 하단
    std::cout << GREEN << "└";
    for (int i = 0; i < boxWidth; i++)
    {
        std::cout << "─";
    }
    std::cout << "┘" << RESET << std::endl;
}

void GameLog::KillAchievement(const std::string& monsterName)
{
    statistics[monsterName + "_killed"]++;
    //logs.push_back("Player killed a " + monsterName + ".");

    if (monsterName == "Goblin" && statistics["Goblin_killed"] == 5)
    {
        if (!IsAchieved("고블린 5마리 처치"))
        {
            CheckAchievement("고블린 5마리 처치");
        }
    }
	if (monsterName == "Bat" && statistics["Bat_killed"] == 5)
    {
        if (!IsAchieved("박쥐 5마리 처치"))
        {
            CheckAchievement("박쥐 5마리 처치");
        }
    }
	if (monsterName == "Slime" && statistics["Slime_killed"] == 5)
    {
        if (!IsAchieved("슬라임 5마리 처치"))
        {
            CheckAchievement("슬라임 5마리 처치");
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
        //logs.push_back(std::string(YELLOW) + "플레이어가 " + std::to_string(amount) + "골드를 획득했습니다." + RESET);

        if (statistics["Gold_Gained"] >= 500 && !IsAchieved("500 골드 획득"))
        {
            CheckAchievement("500 골드 획득");
        }
    }
    else if (amount < 0)
    {
        statistics["Gold_Spent"] += -amount;
        logs.push_back(std::string(YELLOW) +"플레이어가 " + std::to_string(-amount) + "골드를 사용했습니다."+ RESET);

        if (statistics["Gold_Spent"] >= 500 && !IsAchieved("500 골드 사용"))
        {
            CheckAchievement("500 골드 사용");
        }
    }
}

void GameLog::TakeDamageAchievement(int amount)
{
    statistics["Damage_Taken"] += amount;
    //logs.push_back("Player took " + std::to_string(amount) + " damage.");

    if (statistics["Damage_Taken"] >= 1000 && !IsAchieved("받은 데미지 1000 누적"))
    {
        CheckAchievement("받은 데미지 1000 누적");
    }
}

void GameLog::AttackDamageAchievement(int amount)
{
    statistics["Damage_Attack"] += amount;
    //logs.push_back("Player attack " + std::to_string(amount) + " damage.");

    if (statistics["Damage_Attack"] >= 1000 && !IsAchieved("준 데미지 1000 누적"))
    {
        CheckAchievement("준 데미지 1000 누적");
    }
}

void GameLog::LevelAchievement(int level)
{
    logs.push_back(std::string(GREEN)+ std::to_string(level)+"레벨 달성!" + RESET);
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
		logs.push_back(std::string(GREEN)+equipmentName + " 강화에 성공하셨습니다!"+ RESET);
		statistics["upgrade success"]++;
	}
	else if(result==1)
	{
		logs.push_back(std::string(RED)+equipmentName + " 강화에 실패하셨습니다"+ RESET);
		statistics["upgrade fail"]++;
	}
	else
	{
		logs.push_back(std::string(RED)+equipmentName + " downgrade."+ RESET);
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
