﻿#include "GameManager.h"
#include "Goblin.h"
#include "Bat.h"
#include "Slime.h"
#include "GoldenGoblin.h"
#include "Shop.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include "GameLog.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>


// 보스가 아닌 적 가져오기
Monster* GameManager::GenerateMonster(int level) 
{
    int type = rand() % 10;
    switch (type)
    {
    case 0:
    case 1:
    case 2:
    case 3:
        return new Goblin(level);
    case 4:
    case 5:
    case 6: 
        return new Bat(level);
    case 7:
    case 8: 
        return new Slime(level);
    case 9: 
        return new GoldenGoblin(level);
    default: return new Goblin(level);
    }
}
// 보스 가져오기
BossMonster* GameManager::GenerateBossMonster(int level)
{
    return new BossMonster(level);
}

// 플레이어와 적이 싸우는 함수
void GameManager::Battle(Characters& player, Monster& enemy)
{
	std::ostringstream oss;
    enemy.TextArt();

    if (enemy.IsBoss())
    {
        oss << "보스 몬스터 " << enemy.GetName() << " 등장! 체력: " << RED << enemy.GetHealth()<< RESET << ", 공격력: " << RED << enemy.GetAttack() <<RESET << endl;
		GameLog::GetInstance()->PrintAndLog(oss.str());
	}
    else
    {
        oss << "몬스터 " << enemy.GetName() << " 등장! 체력: " <<RED << enemy.GetHealth() << RESET << ", 공격력: " << RED << enemy.GetAttack() << RESET << endl;
		GameLog::GetInstance()->PrintAndLog(oss.str());
	}
        
    // 플레이어와 적 모두 살아있을 경우
    while (player.GetHealth() > 0 && enemy.GetHealth() > 0)
    {   
        if(enemy.IsGoldenGoblin() && BattleCount >= 4)
        {
			oss.str("");
			oss.clear();
            oss << enemy.GetName() << "이(가) 전투에서 도망쳤습니다!" << endl;
			GameLog::GetInstance()->PrintAndLog(oss.str());
            enemy.TakeDamage(enemy.GetHealth()); //체력 0으로 만들어 죽은 상태로 처리

            //턴 초기화
            BattleCount = 1;
            break;
        }

        // 1. 아이템 사용
        if (!player.GetInventory().empty())
        {
            int useItemChance = rand() % 100;
            // 30% 확률
            if (useItemChance < 30)
            {
                // 가지고 있는 아이템 중 랜덤
                int itemIndex = rand() % player.GetInventory().size();
                // 아이템 사용
                player.GetInventory()[itemIndex]->Use(player);
            }
        }


        // 2. 플레이어 -> 적 공격
        // 적의 체력 변화를 보여주기 위한 변수 저장 (예: 50 -> 0)
        int prevEnemyHealth = enemy.GetHealth();
        // 플레이어 -> 적 공격
        enemy.TakeDamage(player.RandomAttack());
        if (player.GetAttackType() == AttackType::Normal)
		{
			oss.str("");
			oss.clear();
			oss << player.GetName() << "이(가) " << enemy.GetName() << "를(을) 공격합니다." << endl;
			GameLog::GetInstance()->PrintAndLog(oss.str());
		}
        else if(player.GetAttackType()==AttackType::Strike)
		{
			oss.str("");
			oss.clear();
			oss << player.GetName() << "이(가) " << enemy.GetName() << "에게 Strike를 사용합니다." << endl;
			GameLog::GetInstance()->PrintAndLog(oss.str());
		}
        else
		{
			oss.str("");
			oss.clear();
			oss << player.GetName() << "이(가) " << enemy.GetName() << "에게 FireBall을 사용합니다." << endl;
			GameLog::GetInstance()->PrintAndLog(oss.str());
		}
		oss.str("");
		oss.clear();
		oss << enemy.GetName() << " 체력: " << GREEN << prevEnemyHealth << RESET << " → " << RED << enemy.GetHealth()<<RESET << endl;
        GameLog::GetInstance()->PrintAndLog(oss.str());
        
        // 3. 적이 죽었을 경우
        if (enemy.GetHealth() <= 0)
        {
            enemy.OnDeath(player);
			GameLog::GetInstance()->KillAchievement(enemy.GetName());
			
            // 플레이어의 경험치가 100이상이고 레벨이 10보다 낮은 경우 레벨업
            while (player.GetExperience() >= 100 && player.GetLevel() < 10)
            {
                player.LevelUp();
				GameLog::GetInstance()->LevelAchievement(player.GetLevel());
            }

            //턴 초기화
            BattleCount = 1;
            break;
        }

        // 4. 적 -> 플레이어 공격
        // 플레이어의 체력 변화를 보여주기 위한 변수 저장 (예: 50 -> 0)
        enemy.AttackPlayer(player);
        

        // 플레이어가 죽었을 경우
        if (player.GetHealth() <= 0)
        {
			oss.str("");
			oss.clear();
            oss << player.GetName() << "가 사망했습니다. 게임 오버!" << endl;
			GameLog::GetInstance()->PrintAndLog(oss.str());

            //턴 초기화
            BattleCount = 1;
            break;
        }

        //플레이어->적, 적->플레이어가 지나면 한 턴 증가
        BattleCount++;
    }
}

// 상점 방문
void GameManager::VisitShop(Characters& player)
{
	std::ostringstream oss;
    string shopChoice;
	while(true)
	{
		cout << "상점을 방문하시겠습니까? (Y/N): ";
		cin >> shopChoice;
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		if(shopChoice == "Y" || shopChoice == "y")
		{
			break;
		}
		else if(shopChoice == "N" || shopChoice == "n")
		{
			cout << "상점을 방문하지 않습니다." << endl;
			return;
		}
		else
		{
			cout << COLOR_RED << "잘못된 입력입니다 Y 혹은 N을 입력해주세요." << COLOR_RESET << endl;
		}
	}
    // 상점 계속 이용
	GameLog::GetInstance()->AddLog("상점에 방문하였습니다.");
	system("cls");
    while (true)
    {
		
        shopInstance.DisplayItems();
        cout << "골드: " << player.GetGold() << endl;
        cout << "1. 아이템 구매 2. 아이템 판매 3. 장비 강화 0. 상점 나가기 " << endl;
        cout << "선택: ";
        int menu = 0;
        cin >> menu;
		if(cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			system("cls");
			cout << COLOR_RED <<  "잘못된 입력입니다." << COLOR_RESET<< endl;
			continue;
		}
        if (menu == 1)
        {
            cout << "구매할 아이템 번호를 선택하세요 (0: 취소): ";
            int choice = 0;
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (choice == 0)
            {
				system("cls");
                continue;
            }
			system("cls");
            shopInstance.BuyItem(choice - 1, player);
        }
        else if (menu == 2)
        {
            player.ShowInventory();
            cout << "판매할 아이템 번호를 선택하세요 (0: 취소): ";
            int sellIdx = 0;
            cin >> sellIdx;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (sellIdx == 0)
            {
				system("cls");
                continue;
            }
			system("cls");
            shopInstance.SellItem(sellIdx - 1, player);
        }
		else if (menu == 3)
		{
			shopInstance.EquipEnhance(player);
			system("cls");
		}
        else if (menu == 0)
        {
			oss.str("");
			oss.clear();
            oss << "상점에서 나갑니다." << endl;
			GameLog::GetInstance()->PrintAndLog(oss.str());
            break;
        }
        else
        {
			system("cls");
            cout << COLOR_RED << "잘못된 입력입니다." << COLOR_RESET<< endl;
        }
    }
}

// 인벤토리 표시
void GameManager::DisplayInventory(Characters& player)
{
    player.ShowInventory();
}
