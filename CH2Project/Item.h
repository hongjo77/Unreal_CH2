#pragma once
#include <string>

class Characters;

class Item
{
protected:
    // 아이템명
    std::string Name;
    int Amount;
public:
    //아이템 생성자
    Item(const std::string& name, int amount) : Name(name), Amount(amount) {}
    //아이템 소멸자
    virtual ~Item() {}
    //캐릭터에게 사용효과를 작성할 순수가상함수
    virtual void Use(Characters& target) = 0;
    // Getter & Setter
    virtual std::string GetName() const { return Name; }
    virtual int GetAmount() { return Amount; }
    virtual void SetAmount(int newAmount) { Amount = newAmount; }
};