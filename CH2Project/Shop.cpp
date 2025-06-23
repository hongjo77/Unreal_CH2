#include "Shop.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include <iostream>

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

void Shop::EquipEnhance(Characters& player) {


    auto EquipList = player.GetEquipments();
    system("cls");
    
    while (true) {
        cout << "현재 소지 금액 " << player.GetGold() << endl;
        cout << "============================================" << endl;
        for (int i = 0; i < EquipList.size(); i++) {
            cout << i + 1 << ". " << EquipList[i]->GetName() << "  강화레벨 : " << EquipList[i]->GetEnLevel() << endl;
        }
        cout << "============================================" << endl;
        cout << "강화할 아이템을 선택하세요 (0: 취소) : ";

        int equipIdx = 0;
        cin >> equipIdx;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (equipIdx == 0) return; 

        if (EquipList[equipIdx - 1]->GetEnLevel() >= 5) {
            cout << "장비 강화가 끝난 장비입니다." << endl;
            return;
        }

        int useGold = (EquipList[equipIdx - 1]->GetEnLevel() + 1) * 5;

        if (player.GetGold() < useGold)
        {
            cout << "골드가 부족합니다." << endl;
            return;
        }
        player.SetGold(player.GetGold() - useGold);

        EquipList[equipIdx - 1]->SetEnLevel(EquipList[equipIdx - 1]->GetEnLevel() + 1);
        EquipList[equipIdx - 1]->SetStat(EquipList[equipIdx - 1]->GetStat() + 5);
    }
    
}