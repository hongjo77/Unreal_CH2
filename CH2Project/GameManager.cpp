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

// ������ �ƴ� �� ��������
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
// ���� ��������
BossMonster* GameManager::GenerateBossMonster(int level)
{
    return new BossMonster(level);
}

// �÷��̾�� ���� �ο�� �Լ�
void GameManager::Battle(Characters& player, Monster& enemy)
{
    if (enemy.IsBoss())
    {
        cout << "���� ���� " << enemy.GetName() << " ����! ü��: " << enemy.GetHealth() << ", ���ݷ�: " << enemy.GetAttack() << endl;
    }
    else
    {
        cout << "���� " << enemy.GetName() << " ����! ü��: " << enemy.GetHealth() << ", ���ݷ�: " << enemy.GetAttack() << endl;
    }
        
    // �÷��̾�� �� ��� ������� ���
    while (player.GetHealth() > 0 && enemy.GetHealth() > 0)
    {
        // 1. ������ ���
        if (!player.GetInventory().empty())
        {
            int useItemChance = rand() % 100;
            // 30% Ȯ��
            if (useItemChance < 30)
            {
                // ������ �ִ� ������ �� ����
                int itemIndex = rand() % player.GetInventory().size();
                // ������ ���
                player.GetInventory()[itemIndex]->Use(player);
                // ������ ��� �� �κ��丮���� ����
                player.GetInventory().erase(player.GetInventory().begin() + itemIndex);
            }
        }


        // 2. �÷��̾� -> �� ����
        // ���� ü�� ��ȭ�� �����ֱ� ���� ���� ���� (��: 50 -> 0)
        int prevEnemyHealth = enemy.GetHealth();
        // �÷��̾� -> �� ����
        enemy.TakeDamage(player.GetAttack());
        cout << player.GetName() << "�� " << enemy.GetName() << "��(��) �����մϴ�! "
            << enemy.GetName() << " ü��: " << prevEnemyHealth << " �� " << enemy.GetHealth() << endl;// ���� �׾��� ���
        
        
        // 3. ���� �׾��� ���
        if (enemy.GetHealth() <= 0)
        {
            cout << enemy.GetName() << " óġ!" << endl;
            // ���� ������ ���
            if (enemy.IsBoss())
            {
                cout << "�����մϴ�! ���� " << enemy.GetName() << "��(��) óġ�ϰ� ������ Ŭ�����߽��ϴ�!" << endl;
            }

            // ���� �������� �� ��� ���
            int goldReward = 10 + rand() % 11;
            // �÷��̾� ����ġ + 50 exp
            player.SetExperience(player.GetExperience() + 50);
            // �÷��̾� ��� + 10~20 ���
            player.SetGold(player.GetGold() + goldReward);
            cout << player.GetName() << "�� 50 EXP�� " << goldReward << " ��带 ȹ���߽��ϴ�. ���� EXP: " << player.GetExperience() << "/100, ���: " << player.GetGold() << endl;
            
            // 4. 30% Ȯ���� ������ ���
            int dropChance = rand() % 100;
            if (dropChance < 30)
            {
                Item* droppedItem = enemy.DropItem();
                if (droppedItem)
                {
                    player.GetInventory().push_back(droppedItem);
                    cout << droppedItem->GetName() << " �������� ȹ���߽��ϴ�!" << endl;
                }
            }

            // �÷��̾��� ����ġ�� 100�̻��̰� ������ 10���� ���� ��� ������
            while (player.GetExperience() >= 100 && player.GetLevel() < 10)
            {
                player.LevelUp();
            }
            break;
        }

        // 5. �� -> �÷��̾� ����
        // �÷��̾��� ü�� ��ȭ�� �����ֱ� ���� ���� ���� (��: 50 -> 0)
        int prevPlayerHealth = player.GetHealth();
        int newHealth = prevPlayerHealth - enemy.GetAttack();

        if (newHealth < 0)
        {
            newHealth = 0;
        }
        player.SetHealth(newHealth);
        cout << enemy.GetName() << "�� " << player.GetName() << "�� �����մϴ�! "
            << player.GetName() << " ü��: " << prevPlayerHealth << " �� " << player.GetHealth() << endl;
        cout << endl;

        // �÷��̾ �׾��� ���
        if (player.GetHealth() <= 0)
        {
            cout << player.GetName() << "�� ����߽��ϴ�. ���� ����!" << endl;
            break;
        }
    }
}

// ���� �湮
void GameManager::VisitShop(Characters& player)
{
    char shopChoice;
    cout << "������ �湮�Ͻðڽ��ϱ�? (Y/N): ";
    cin >> shopChoice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (shopChoice != 'Y' && shopChoice != 'y')
    {
        cout << "������ �湮���� �ʽ��ϴ�." << endl;
        return;
    }
    // ���� ��� �̿�
    while (true)
    {
        shopInstance.DisplayItems();
        cout << "���: " << player.GetGold() << endl;
        cout << "1. ������ ����  2. ������ �Ǹ�  0. ���� ������" << endl;
        cout << "����: ";
        int menu = 0;
        cin >> menu;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (menu == 1)
        {
            cout << "������ ������ ��ȣ�� �����ϼ��� (0: ���): ";
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
            cout << "�Ǹ��� ������ ��ȣ�� �����ϼ��� (0: ���): ";
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
            cout << "�������� �����ϴ�." << endl;
            break;
        }
        else
        {
            cout << "�߸��� �Է��Դϴ�." << endl;
        }
    }
}

// �κ��丮 ǥ��
void GameManager::DisplayInventory(Characters& player)
{
    player.ShowInventory();
}
