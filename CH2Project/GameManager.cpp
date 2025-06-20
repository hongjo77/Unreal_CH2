#include "GameManager.h"
#include "Goblin.h"
#include "Orc.h"
#include "Troll.h"
#include "Shop.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
// 게임 매니저 테스트

// 보스가 아닌 적 가져오기
Monster* GameManager::GenerateMonster(int level) 
{
    int type = rand() % 3;
    switch (type)
    {
    case 0: return new Goblin(level);
    case 1: return new Orc(level);
    case 2: return new Troll(level);
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
    if (enemy.IsBoss())
    {
        cout << "보스 몬스터 " << enemy.GetName() << " 등장! 체력: " << enemy.GetHealth() << ", 공격력: " << enemy.GetAttack() << endl;
    }
    else
    {
        cout << "몬스터 " << enemy.GetName() << " 등장! 체력: " << enemy.GetHealth() << ", 공격력: " << enemy.GetAttack() << endl;
    }
        
    // 플레이어와 적 모두 살아있을 경우
    while (player.GetHealth() > 0 && enemy.GetHealth() > 0)
    {
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
                // 아이템 사용 후 인벤토리에서 제거
                player.GetInventory().erase(player.GetInventory().begin() + itemIndex);
            }
        }


        // 2. 플레이어 -> 적 공격
        // 적의 체력 변화를 보여주기 위한 변수 저장 (예: 50 -> 0)
        int prevEnemyHealth = enemy.GetHealth();
        // 플레이어 -> 적 공격
        enemy.TakeDamage(player.GetAttack());
        cout << player.GetName() << "가 " << enemy.GetName() << "을(를) 공격합니다! "
            << enemy.GetName() << " 체력: " << prevEnemyHealth << " → " << enemy.GetHealth() << endl;// 적이 죽었을 경우
        
        
        // 3. 적이 죽었을 경우
        if (enemy.GetHealth() <= 0)
        {
            cout << enemy.GetName() << " 처치!" << endl;
            // 적이 보스일 경우
            if (enemy.IsBoss())
            {
                cout << "축하합니다! 보스 " << enemy.GetName() << "을(를) 처치하고 게임을 클리어했습니다!" << endl;
            }

            // 적을 물리쳤을 때 얻는 골드
            int goldReward = 10 + rand() % 11;
            // 플레이어 경험치 + 50 exp
            player.SetExperience(player.GetExperience() + 50);
            // 플레이어 골드 + 10~20 골드
            player.SetGold(player.GetGold() + goldReward);
            cout << player.GetName() << "가 50 EXP와 " << goldReward << " 골드를 획득했습니다. 현재 EXP: " << player.GetExperience() << "/100, 골드: " << player.GetGold() << endl;
            
            // 4. 30% 확률로 아이템 드랍
            int dropChance = rand() % 100;
            if (dropChance < 30)
            {
                Item* droppedItem = enemy.DropItem();
                if (droppedItem)
                {
                    player.GetInventory().push_back(droppedItem);
                    cout << droppedItem->GetName() << " 아이템을 획득했습니다!" << endl;
                }
            }

            // 플레이어의 경험치가 100이상이고 레벨이 10보다 낮은 경우 레벨업
            while (player.GetExperience() >= 100 && player.GetLevel() < 10)
            {
                player.LevelUp();
            }
            break;
        }

        // 5. 적 -> 플레이어 공격
        // 플레이어의 체력 변화를 보여주기 위한 변수 저장 (예: 50 -> 0)
        int prevPlayerHealth = player.GetHealth();
        int newHealth = prevPlayerHealth - enemy.GetAttack();

        if (newHealth < 0)
        {
            newHealth = 0;
        }
        player.SetHealth(newHealth);
        cout << enemy.GetName() << "이 " << player.GetName() << "를 공격합니다! "
            << player.GetName() << " 체력: " << prevPlayerHealth << " → " << player.GetHealth() << endl;
        cout << endl;

        // 플레이어가 죽었을 경우
        if (player.GetHealth() <= 0)
        {
            cout << player.GetName() << "가 사망했습니다. 게임 오버!" << endl;
            break;
        }
    }
}

// 상점 방문
void GameManager::VisitShop(Characters& player)
{
    char shopChoice;
    cout << "상점을 방문하시겠습니까? (Y/N): ";
    cin >> shopChoice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (shopChoice != 'Y' && shopChoice != 'y')
    {
        cout << "상점을 방문하지 않습니다." << endl;
        return;
    }
    // 상점 계속 이용
    while (true)
    {
        shopInstance.DisplayItems();
        cout << "골드: " << player.GetGold() << endl;
        cout << "1. 아이템 구매  2. 아이템 판매  0. 상점 나가기" << endl;
        cout << "선택: ";
        int menu = 0;
        cin >> menu;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (menu == 1)
        {
            cout << "구매할 아이템 번호를 선택하세요 (0: 취소): ";
            int choice = 0;
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (choice == 0)
            {
                continue;
            }
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
                continue;
            }
            shopInstance.SellItem(sellIdx - 1, player);
        }
        else if (menu == 0)
        {
            cout << "상점에서 나갑니다." << endl;
            break;
        }
        else
        {
            cout << "잘못된 입력입니다." << endl;
        }
    }
}

// 인벤토리 표시
void GameManager::DisplayInventory(Characters& player)
{
    player.ShowInventory();
}
