#define NOMINMAX
#include "Shop.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include "GameLog.h"
#include "Color.h"
#include <iostream>
#include <Windows.h>
#include <cstdlib>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

// 아이템 목록 생성
Shop::Shop()
{
    AvailableItems.push_back(new HealthPotion());
    AvailableItems.push_back(new AttackBoost());
}

Shop::~Shop()
{
    for (auto item : AvailableItems)
    {
        delete item;
    }
}

// 진열대 출력
void Shop::DisplayItems() const
{
    cout << "구매 가능한 아이템:" << endl;
    for (size_t i = 0; i < AvailableItems.size(); i++)
    {
        string name = AvailableItems[i]->GetName();
        int price = (name == "Health Potion") ? 10 : 15;
        cout << (i + 1) << ". " << name;
        if (name == "Health Potion")
        {
            cout << " (체력 +50): ";
        }
        else if (name == "Attack Boost")
        {
            cout << " (공격력 +10): ";
        }
        cout << price << " 골드" << endl;
    }
}

// 아이템 구매
void Shop::BuyItem(int index, Characters& player)
{
    // 인덱스 확인
    if (index < 0 || index >= (int)AvailableItems.size())
    {
        cout << "잘못된 인덱스입니다." << endl;
        return;
    }

    string name = AvailableItems[index]->GetName();
    
    cout << name << "을(를) 선택하셨습니다. 구매 개수 선택 (0: 취소) : ";
    int count = 0;
    cin >> count;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "잘못된 입력입니다." << endl;
    }
    else {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (count == 0) {
        cout << "아이템 구매를 취소하셨습니다.\n" << endl;
        return;
    }

    // 힐포션 선택하면 10원 아니면 (Attack boost인경우) 15원
    int price = (name == "Health Potion") ? 10 : 15;
    if (player.GetGold() < price * count)
    {
        cout << "골드가 부족합니다.\n" << endl;
        return;
    }
    
    auto& inv = player.GetInventory();
    inv[index]->SetAmount(inv[index]->GetAmount() + count);

    player.SetGold(player.GetGold() - (price * count));
    cout << inv[index]->GetName() << "을(를) "<< count << "개 구매했습니다!\n" << endl;
    GameLog::GetInstance()->GoldAchievement(- (price * count));
    
}

// 아이템 판매
void Shop::SellItem(int index, Characters& player)
{
    auto& inv = player.GetInventory();
    // 인덱스 확인
    if (index < 0 || index >= (int)inv.size())
    {
        cout << "잘못된 인덱스입니다." << endl;
        return;
    }
    string name = inv[index]->GetName();
    cout << name << "을(를) 선택하셨습니다. (현재 소지 개수 : " << inv[index]->GetAmount() << ")" << endl;
    if (inv[index]->GetAmount() <= 0) {
        cout << "판매 할 수 있는 수량이 없습니다.\n" << endl;
        return;
    }

    while (true) {

        cout << "판매 개수 선택(0: 취소) : ";
        int count = 0;
        cin >> count;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "잘못된 입력입니다." << endl;
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (count == 0) {
            cout << "아이템 판매를 취소하셨습니다.\n" << endl;
            return;
        }

        // 힐포션 선택하면 10원 아니면 (Attack boost인경우) 15원
        int price = (name == "Health Potion") ? 10 : 15;
        // 원래 가격의 60%만 지급
        int sellPrice = static_cast<int>(price * 0.6);

        if (inv[index]->GetAmount() < count) {
            cout << "판매 가능한 개수를 넘었습니다.\n" << endl;
            continue;
        }

        player.SetGold(player.GetGold() + (sellPrice * count));
        cout << inv[index]->GetName() << "을(를) " << count << "개 판매했습니다. " << sellPrice * count << " 골드를 받았습니다.\n" << endl;

        inv[index]->SetAmount(inv[index]->GetAmount() - count);
        break;
    }
    
}

int EnhanceLogic(int EnLevel) {
    if (EnLevel == 0) {
        return 90;
    }
    else if (EnLevel == 1) {
        return 75;
    }
    else if (EnLevel == 2) {
        return 60;
    }
    else if (EnLevel == 3) {
        return 45;
    }
    else if (EnLevel == 4) {
        return 30;
    }

    return 0;
}

void Shop::EquipEnhance(Characters& player) {


    auto EquipList = player.GetEquipments();
    
    while (true) {
        system("cls");
        cout << "현재 소지 금액 " << player.GetGold() << endl;
        cout << YELLOW << "============================================" <<  endl;
        for (int i = 0; i < EquipList.size(); i++) {
            cout << i + 1 << ". " << EquipList[i]->GetName() << "  강화레벨 : " << EquipList[i]->GetEnLevel();
            if (EquipList[i]->GetEnLevel() == 5) {
                cout << "  강화 소모 골드 : -" << endl;
            }
            else {
                cout << "  강화 소모 골드 : " << (EquipList[i]->GetEnLevel() + 1) * 5 << endl;
            }
            
        }
        cout << "============================================" << RESET << endl;
        cout << "강화할 아이템을 선택하세요 (0: 취소) : ";

        int equipIdx = 0;
        cin >> equipIdx;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            equipIdx = EquipList.size() + 1;
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (equipIdx == 0) return;
        if (equipIdx > EquipList.size()) {
            cout << "잘못된 입력입니다." << endl;
            system("pause");
            continue;
        }

        int EnLevel = EquipList[equipIdx - 1]->GetEnLevel();
        int Stat = EquipList[equipIdx - 1]->GetStat();

        if (EnLevel >= 5) {
            cout << "장비 강화가 끝난 장비입니다. \n" << endl;
            system("pause");
            continue;
        }

        int useGold = (EnLevel + 1) * 5;

        if (player.GetGold() < useGold)
        {
            cout << "골드가 부족합니다. \n" << endl;
            system("pause");
            continue;
        }
        player.SetGold(player.GetGold() - useGold);
		GameLog::GetInstance()->GoldAchievement(-useGold);

        //확률
        int probability = rand() % 100;

        /*
        for (int i = 3; i > 0; i--) {
            cout << "땅";
            Sleep(500);
        }*/
        int count = 0;
        while (count < 6) {
            if (count % 2 == 0) {
                system("cls");
                cout << "_____________" << endl;
                cout << "|            |" << endl;
                cout << "|____________|" << endl;
                cout << "     |  |        " << endl;
                cout << "     |  |        " << endl;
                cout << "     |  |        " << endl;
                cout << "     |  |        " << endl;
                cout << "     |__|        " << endl;

                Sleep(300);
                count++;
            }
            else {
                system("cls");
                cout << "             _____" << endl;
                cout << "             |    |" << endl;
                cout << "_____________|    |" << endl;
                cout << "|____________|    |   땅~" << endl;
                cout << "             |    |" << endl;
                cout << "             |____|" << endl;
                cout << "\x1b[91m""         +*\\*\\+*+*/+/+*" << RESET << endl;
                cout << RED << "           *\\*\\+*/+/+" << RESET << endl;

                Sleep(300);
                count++;
            }
        }

        if (probability < EnhanceLogic(EnLevel)) {
            cout << GREEN << "\n강화에 성공하셨습니다! \n" << RESET << endl;
            EquipList[equipIdx - 1]->SetEnLevel(EnLevel + 1);
            EquipList[equipIdx - 1]->SetStat(Stat + 7);

            GameLog::GetInstance()->EquipmentAchievement(
                EquipList[equipIdx - 1]->GetName(),
                EquipList[equipIdx - 1]->GetEnLevel(),
                0
            );

            system("pause");
        }
        else {
            cout << RED << "\n강화에 실패하셨습니다. \n" << RESET << endl;
            GameLog::GetInstance()->EquipmentAchievement(
                EquipList[equipIdx - 1]->GetName(),
                EquipList[equipIdx - 1]->GetEnLevel(),
                1
            );

            if (0 == rand() % 5) {
                cout << RED << "강화에 실패하여 강화 레벨이 하락하였습니다. \n" << RESET << endl;
                EquipList[equipIdx - 1]->SetEnLevel(EnLevel - 1);
                EquipList[equipIdx - 1]->SetStat(Stat - 5);

                GameLog::GetInstance()->EquipmentAchievement(
                    EquipList[equipIdx - 1]->GetName(),
                    EquipList[equipIdx - 1]->GetEnLevel(),
                    2
                );
            }

            system("pause");

        }
    }
}