#include "Shop.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include <iostream>

// ������ ��� ����
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

// ������ ���
void Shop::DisplayItems() const
{
    cout << "���� ������ ������:" << endl;
    for (size_t i = 0; i < AvailableItems.size(); i++)
    {
        string name = AvailableItems[i]->GetName();
        int price = (name == "Health Potion") ? 10 : 15;
        cout << (i + 1) << ". " << name;
        if (name == "Health Potion")
        {
            cout << " (ü�� +50): ";
        }
        else if (name == "Attack Boost")
        {
            cout << " (���ݷ� +10): ";
        }
        cout << price << " ���" << endl;
    }
}

// ������ ����
void Shop::BuyItem(int index, Characters& player)
{
    // �ε��� Ȯ��
    if (index < 0 || index >= (int)AvailableItems.size())
    {
        cout << "�߸��� �ε����Դϴ�." << endl;
        return;
    }

    string name = AvailableItems[index]->GetName();
    // ������ �����ϸ� 10�� �ƴϸ� (Attack boost�ΰ��) 15��
    int price = (name == "Health Potion") ? 10 : 15;
    if (player.GetGold() < price)
    {
        cout << "��尡 �����մϴ�." << endl;
        return;
    }
    // �������� ���� �����ؼ� �÷��̾�� �ѱ� (������ ����ǰ�� ����)
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
    cout << item->GetName() << "��(��) �����߽��ϴ�!" << endl;
}

// ������ �Ǹ�
void Shop::SellItem(int index, Characters& player)
{
    auto& inv = player.GetInventory();
    // �ε��� Ȯ��
    if (index < 0 || index >= (int)inv.size())
    {
        cout << "�߸��� �ε����Դϴ�." << endl;
        return;
    }
    string name = inv[index]->GetName();
    // ������ �����ϸ� 10�� �ƴϸ� (Attack boost�ΰ��) 15��
    int price = (name == "Health Potion") ? 10 : 15;
    // ���� ������ 60%�� ����
    int sellPrice = static_cast<int>(price * 0.6);

    player.SetGold(player.GetGold() + sellPrice);
    cout << inv[index]->GetName() << "��(��) �Ǹ��߽��ϴ�. " << sellPrice << " ��带 �޾ҽ��ϴ�." << endl;
    delete inv[index];
    // �÷��̾��� �κ��丮������ ����
    inv.erase(inv.begin() + index);
}
