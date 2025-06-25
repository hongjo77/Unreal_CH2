#include "Characters.h"
#include "Shop.h"
#include <iostream>
#include <random>
#include "Chest.h"
#include "Weapon.h"
#include "Leg.h"
#include "Helmet.h"

Characters* Characters::Instance = nullptr;

Characters::Characters(const string& inName)
    : Name(inName), Level(1), Health(200), MaxHealth(200), Attack(30), Experience(0), Gold(0), MaxMana(100),CurrentMana(100)
{
    this->InitEquipment();
    this->Inventory = {new HealthPotion(), new AttackBoost()};
    cout << "캐릭터 " << Name << " 생성 완료! 레벨: " << Level << ", 체력: " << Health << ", 공격력: " << Attack << endl;
    cout << endl;
}

Characters* Characters::GetInstance(const string& inName)
{
    if (!Instance)
    {
        Instance = new Characters(inName);
    }
    return Instance;
}

string Characters::GetName() const { return Name; }

void Characters::DisplayStatus() const
{
    cout << "이름: " << Name << " | 레벨: " << Level << " | 체력: " << Health << "/" << MaxHealth
        << " | 공격력: " << Attack << " | 경험치: " << Experience << " | 골드: " << Gold << endl;
}

void Characters::LevelUp()
{
    // 최대 레벨 10
    if (Level >= 10)
    {
        return;
    }
    Experience -= 100;
    Level++;
    MaxHealth += Level * 20;
    Attack += Level * 5;
    Health = MaxHealth;
    cout << "레벨업! 현재 레벨: " << Level << " | 체력: " << MaxHealth << " | 공격력: " << Attack << endl;
}

void Characters::ShowInventory() const
{
    cout << "--- 인벤토리 ---" << endl;
    if (Inventory.empty())
    {
        cout << " (비어있음)" << endl;
        return;
    }
    // 인벤토리 아이템 전부 출력
    for (size_t i = 0; i < Inventory.size(); i++)
    {
        cout << (i + 1) << ". " << Inventory[i]->GetName() <<" 수량:"<<Inventory[i]->GetAmount() << endl;
    }
}

int Characters::RandomSkill()
{
    srand(time(NULL));

    int type = rand() % 3;
    currentAttackType = static_cast<AttackType>(type);
    return type;
}

int Characters::GetAttack()
{
    //공격 타입 설정
    Characters::RandomSkill();
    int Attack = this->Attack + this->weapon->GetStat();

    auto recoverMana = [this](int n)
        {   
                CurrentMana += n;

            if (CurrentMana > MaxMana)
                CurrentMana = MaxMana;
        };

    switch (currentAttackType)
    {
    case AttackType::Normal:
        recoverMana(10);
        return Attack;
    
    case AttackType::Strike:
        if (CurrentMana >= 20)
        {
            cout <<"플레이어가 Strike 스킬을 사용합니다." << endl;
            CurrentMana -= 20;
            return Attack + 20;
        }
        else
        {
            recoverMana(10);
            return Attack;
        }
    
    case AttackType::FireBall:
        if (CurrentMana >= 50)
        {
            cout << "플레이어가 FireBall 스킬을 사용합니다." << endl;
            CurrentMana -= 50;
            return Attack + 40;
        }

        else
        {
            recoverMana(10);
            return Attack;
        }

    default:
        recoverMana(10);
        return Attack;
    }
}

void Characters::InitEquipment()
{
    this->chest = new Chest();
    this->helmet = new Helmet();
    this->weapon = new Weapon();
    this->leg = new Leg();
     
}

Characters::~Characters()
{
    // 장비 해제
    delete weapon;
    delete helmet;
    delete chest;
    delete leg;

    // 인벤토리 해제
    for (auto item : Inventory) {
        delete item;
    }
    Inventory.clear();
}

int Characters::GetTotalArmorStat()
{
    //생성자로 항상 기본장비가 있기 때문에 체크 필요 x
    int total = 0;
    total = this->helmet->GetStat() + this->chest->GetStat() + this->leg->GetStat();
    return total;
 }

vector<Equipment*> Characters::GetEquipments()
{
    vector<Equipment*> tmp;
    tmp = { this->weapon, this->helmet,this->chest,this->leg };
    return tmp;
}

// 멤버 변수 Getter Setter
int Characters::GetHealth() const { return Health; }
void Characters::SetHealth(int newHealth) { Health = newHealth; }
int Characters::GetMaxHealth() const { return MaxHealth; }
void Characters::SetAttack(int newAttack) { Attack = newAttack; }
int Characters::GetLevel() const { return Level; }
void Characters::SetLevel(int newLevel) { Level = newLevel; }
int Characters::GetExperience() const { return Experience; }
void Characters::SetExperience(int newExp) { Experience = newExp; }
int Characters::GetGold() const { return Gold; }
void Characters::SetGold(int newGold) { Gold = newGold; }
vector<Item*>& Characters::GetInventory() { return Inventory; }
int Characters::GetBaseAttack() { return Attack; }
