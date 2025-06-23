#pragma once
#include <vector>
#include "Item.h"
#include "Characters.h"

using namespace std;

class Shop
{
private:
    vector<Item*> AvailableItems;
    
public:
    Shop();
    ~Shop();

    void DisplayItems() const;
    void BuyItem(int index, Characters& player);
    void SellItem(int index, Characters& player);

    //장비강화 추가!!!
    void EquipEnhance(int index, Characters& player);

};
