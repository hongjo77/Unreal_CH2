#include "Characters.h"
#include "GameManager.h"
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    string Name;
    cout << "캐릭터 이름을 입력하세요: ";
    getline(cin, Name);

    // 캐릭터 인스턴스 생성
    Characters* player = Characters::GetInstance(Name);
    GameManager manager;

    // 플레이어가 죽지 않거나 10레벨이 아직 안된 경우
    while (player->GetHealth() > 0 && player->GetLevel() < 10)
    {
        // 스테이터스 출력
        system("cls");
        player->DisplayStatus();
        cout << endl;

        // 적 생성
        Monster* enemy = manager.GenerateMonster(player->GetLevel());
        // 전투 진입
        manager.Battle(*player, *enemy);
        delete enemy;

        // 플레이어 사망
        if (player->GetHealth() <= 0)
        {
            break;
        }
        // 상점 방문
        manager.VisitShop(*player);
    }

    // 10레벨이면 보스전 입장
    if (player->GetLevel() >= 10)
    {
        system("cls");
        player->DisplayStatus();
        cout << endl;

        // 보스 생성
        BossMonster* boss = manager.GenerateBossMonster(player->GetLevel());
        // 보스 전투
        manager.Battle(*player, *boss);
        delete boss;
    }

    cout << "게임이 종료되었습니다." << endl;
    return 0;
}
