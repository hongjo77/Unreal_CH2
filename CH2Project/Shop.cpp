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
    
    //as-is
    /*
    // 아이템은 새로 생성해서 플레이어에게 넘김 (상점의 진열품은 예시)
    Item* item = nullptr;
    
    if (name == "Health Potion")
    {
        item = new HealthPotion();
    }
    else if (name == "Attack Boost")
    {
        item = new AttackBoost();
    }
    player.GetInventory().push_back(item);
    cout << item->GetName() << "을(를) 구매했습니다!" << endl;
    */

    //-----------------to be---------------
    auto& inv = player.GetInventory();
    inv[index]->SetAmount(inv[index]->GetAmount() + 1);

    player.SetGold(player.GetGold() - price);
    cout << inv[index]->GetName() << "을(를) 구매했습니다!" << endl;
    //-----------------------------------------
    
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

    player.SetGold(player.GetGold() + sellPrice);
    cout << inv[index]->GetName() << "을(를) 판매했습니다. " << sellPrice << " 골드를 받았습니다." << endl;
   
    //as-is
    /*
    delete inv[index];
    // 플레이어의 인벤토리에서도 삭제
    inv.erase(inv.begin() + index);
    */
    //-----------------to be---------------
    inv[index]->SetAmount(inv[index]->GetAmount() - 1);
    //-----------------------------------------
}

void EnhanceLogic(Equipment& equip, Characters& player) {

    //강화레벨에 따른 강화확률과 소모되는 돈
    // 0 = 90, 5
    // 1 = 75, 10
    // 2 = 60, 15
    // 3 = 45, 20
    // 4 = 30, 30

    //강화 확률
    int probability = rand() % 90 - (equip.GetEnLevel() * 15);

    //강화 시도 시 골드 소모
    int useGold = (equip.GetEnLevel() + 1) * 5;

    if (equip.GetEnLevel() <= 5) {
        cout << "장비 강화가 끝난 장비입니다." << endl;
        return;
    }

    if (player.GetGold() < useGold)
    {
        cout << "골드가 부족합니다." << endl;
        return;
    }
    player.SetGold(player.GetGold() - useGold);

    equip.SetEnLevel(equip.GetEnLevel() + 1);
    equip.SetStat(equip.GetStat() + 5);

}

void Shop::EquipEnhance(Characters& player) {


    //auto& EquipList = player.GetEquipments();
    system("cls");
    /*
    while (true) {

        cout << "============================================" << endl;
        for (int i = 0; i < EquipList.size(); i++) {
            cout << i + 1 << ". " << EquipList[i]->GetName() << "  강화레벨 : " << EquipList[i]->GetEnLevel() << endl;
        }
        cout << "============================================" << endl;
        cout << "강화할 아이템을 선택하세요 (0: 취소) : ";

        int equipIdx = 0;
        cin >> equipIdx;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int useGold = (EquipList[equipIdx]->GetEnLevel() + 1) * 5;

        if (EquipList[equipIdx]->GetEnLevel() <= 5) {
            cout << "장비 강화가 끝난 장비입니다." << endl;
            return;
        }

        if (player.GetGold() < useGold)
        {
            cout << "골드가 부족합니다." << endl;
            return;
        }
        player.SetGold(player.GetGold() - useGold);

        EquipList[equipIdx]->SetEnLevel(EquipList[equipIdx]->GetEnLevel() + 1);
        EquipList[equipIdx]->SetStat(EquipList[equipIdx]->GetStat() + 5);
    }
    */
}