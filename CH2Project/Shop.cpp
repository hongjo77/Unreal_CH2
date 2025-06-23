#include "Shop.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
//include "Helmet.h"
//include "Chest.h"
//include "Leg.h"
//include "Weapon.h"
#include <iostream>

// 아이템 목록 생성
Shop::Shop()
{
    AvailableItems.push_back(new HealthPotion());
    AvailableItems.push_back(new AttackBoost());

    //추가!!!
    /*
    EquitList.push_back(new Helmet());
    EquitList.push_back(new Chest());
    EquitList.push_back(new Leg());
    EquitList.push_back(new Weapon());
    */

}

Shop::~Shop()
{
    for (auto item : AvailableItems)
    {
        delete item;
    }

    /*
    for (auto Equit : EquitList)
    {
        delete Equit;
    }
    */

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

    player.SetGold(player.GetGold() - price);
    player.GetInventory().push_back(item);
    cout << item->GetName() << "을(를) 구매했습니다!" << endl;
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
    delete inv[index];
    // 플레이어의 인벤토리에서도 삭제
    inv.erase(inv.begin() + index);
}

//장비강화 추가!!!
void EquipEnhance(int index, Characters& player) {
   
    //player.get장비창[index]
    
}