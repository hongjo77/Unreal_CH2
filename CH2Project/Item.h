#pragma once
#include <iostream>
#include <string>
using namespace std;

class Characters;

class Item
{
protected:
    // 아이템명
    string Name;
public:
    //아이템 생성자
    Item(const string& name) : Name(name) {}
    //아이템 소멸자
    virtual ~Item() {}
    //아이템명을 넘겨주는 메서드 
    virtual string GetName() const { return Name; }
    //캐릭터에게 사용효과를 작성할 순수가상함수
    virtual void Use(Characters& target) = 0;
};