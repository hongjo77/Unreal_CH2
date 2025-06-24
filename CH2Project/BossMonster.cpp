#include "BossMonster.h"
#include <iostream>

BossMonster::BossMonster(int level)
    : Monster(
        "Orc Shaman",
        (rand() % (level * 50)) + (level * 100),
        (rand() % (level * 10)) + (level * 20)
    ), SkillAttack(rand() % (level * 10) + (level*50)){}

// 보스인지 아닌지 확인
bool BossMonster::IsBoss() const { return true; }

void BossMonster::OnDeath(Characters& player) 
{
    cout << endl;
    cout << Name << " 처치!" << endl;
    cout << "축하합니다! 보스 " << Name << "을(를) 처치하고 게임을 클리어했습니다!" << endl;
}

void BossMonster::AttackPlayer(Characters& player) 
{
    int prevPlayerHealth = player.GetHealth();
    bool IsSkill = false; //스킬 사용 여부
    int newHealth = 0;

    //30% 확률로 스킬 공격
    int skillChance = rand() % 100;
    if (skillChance < 30)
    {
        cout << Name << "이(가) 강력한 기술로 " << player.GetName() << "를 공격합니다! ";
        IsSkill = true;
        newHealth = prevPlayerHealth - SkillAttack;
    }
    else
    {
        cout << Name << "이(가) " << player.GetName() << "를 공격합니다! ";
        newHealth = prevPlayerHealth - Attack;
    }

    if (newHealth < 0)
    {
        newHealth = 0;
    }
    player.SetHealth(newHealth);

    cout<< player.GetName() << " 체력: " << prevPlayerHealth << " → " << player.GetHealth() << endl;

    // 일반 공격 시 각각 20% 확률로 공격력 감소, 방어력 감소 디버프
    if (!IsSkill)
    {
        int debuffChance = rand() % 100;
        if (debuffChance >= 0 && debuffChance < 20)
        {
            int prevPlayerAttack = player.GetBaseAttack();
            int DroppedPlayerAttack = static_cast<int>(player.GetBaseAttack() * 0.8);
            player.SetAttack(DroppedPlayerAttack);
            cout << player.GetName() << "이 공격력 감소 디버프에 걸렸습니다! "
                << player.GetName() << " 공격력: " << prevPlayerAttack << " → " << player.GetBaseAttack() << endl;
        }
        /*
        else if(debuffChance >=20 && debuffChance <=40)
        {

        }
        */
    }
    cout << endl;
}
