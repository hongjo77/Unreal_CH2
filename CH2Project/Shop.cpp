#define NOMINMAX
#include "Shop.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include <iostream>
#include <Windows.h>

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
    // 힐포션 선택하면 10원 아니면 (Attack boost인경우) 15원
    int price = (name == "Health Potion") ? 10 : 15;
    if (player.GetGold() < price)
    {
        cout << "골드가 부족합니다." << endl;
        return;
    }
    
    auto& inv = player.GetInventory();
    inv[index]->SetAmount(inv[index]->GetAmount() + 1);

    player.SetGold(player.GetGold() - price);
    cout << inv[index]->GetName() << "을(를) 구매했습니다!" << endl;
    
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
    // 힐포션 선택하면 10원 아니면 (Attack boost인경우) 15원
    int price = (name == "Health Potion") ? 10 : 15;
    // 원래 가격의 60%만 지급
    int sellPrice = static_cast<int>(price * 0.6);

    if (inv[index]->GetAmount() <= 0) {
        cout << "더 이상 판매 할 수 없습니다." << endl;
        return;
    }

    player.SetGold(player.GetGold() + sellPrice);
    cout << inv[index]->GetName() << "을(를) 판매했습니다. " << sellPrice << " 골드를 받았습니다." << endl;

    inv[index]->SetAmount(inv[index]->GetAmount() - 1);

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
    system("cls");
    
    while (true) {
        cout << "현재 소지 금액 " << player.GetGold() << endl;
        cout << "============================================" << endl;
        for (int i = 0; i < EquipList.size(); i++) {
            cout << i + 1 << ". " << EquipList[i]->GetName() << "  강화레벨 : " << EquipList[i]->GetEnLevel() << "  강화 소모 골드 : " << (EquipList[i]->GetEnLevel() + 1) * 5 << endl;
        }
        cout << "============================================" << endl;
        cout << "강화할 아이템을 선택하세요 (0: 취소) : ";

        int equipIdx = 0;
        cin >> equipIdx;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (equipIdx == 0) return;

        int EnLevel = EquipList[equipIdx - 1]->GetEnLevel();
        int Stat = EquipList[equipIdx - 1]->GetStat();

        if (EnLevel >= 5) {
            cout << "장비 강화가 끝난 장비입니다. \n" << endl;
            continue;
        }

        int useGold = (EnLevel + 1) * 5;

        if (player.GetGold() < useGold)
        {
            cout << "골드가 부족합니다. \n" << endl;
            continue;
        }
        player.SetGold(player.GetGold() - useGold);

        //확률
        int probability = rand() % 100;

        for (int i = 3; i > 0; i--) {
            cout << "땅";
            Sleep(500);
        }

        if (probability < EnhanceLogic(EnLevel)) {
            cout << "\n강화에 성공하셨습니다! \n" << endl;
            EquipList[equipIdx - 1]->SetEnLevel(EnLevel + 1);
            EquipList[equipIdx - 1]->SetStat(Stat + 5);
        }
        else {
            cout << "\n강화에 실패하셨습니다. \n" << endl;
        }
    }
    
}