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

    //주석추가
};
