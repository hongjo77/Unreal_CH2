#include "Characters.h"
#include "GameManager.h"
#include "GameLog.h"
#include "Color.h"
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    string Name;
	while (true)
	{
		cout << "캐릭터 이름을 입력하세요: ";
		getline(cin, Name);

		// 이름이 비었거나 맨 앞이 공백이면 다시 입력
		if (Name.empty() || Name[0] == ' ') {
			cout << RED << "이름은 공백으로 시작할 수 없습니다. 다시 입력해주세요." << RESET << endl;
			continue;
		}
		break;
	}


    // 캐릭터 인스턴스 생성
    Characters* player = Characters::GetInstance(Name);
    GameManager manager;

	int count=1;
    // 플레이어가 죽지 않거나 10레벨이 아직 안된 경우
    while (player->GetHealth() > 0 && player->GetLevel() < 10)
    {
		// 로그에 층 추가
		GameLog::GetInstance()->AddLog(BLUE+to_string(count)+"층"+RESET);
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

		count++;
    }

    // 10레벨이면 보스전 입장
    if (player->GetLevel() >= 10)
    {
		GameLog::GetInstance()->AddLog(std::string(BLUE)+"보스층"+RESET);
        system("cls");
        player->DisplayStatus();
        cout << endl;

        // 보스 생성
        BossMonster* boss = manager.GenerateBossMonster(player->GetLevel());
        // 보스 전투
        manager.Battle(*player, *boss);
        delete boss;
    }

	while (true)
    {
        cout << "1. 로그 출력 2. 통계 출력 3. 업적 출력 0. 게임 종료" << endl;
        cout << "선택: ";
        int logChoice = 0;
        cin >> logChoice;
        if (cin.fail())
		{
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
			cout << RED << "잘못된 입력입니다." << RESET << endl;
			continue;
        }

        if (logChoice == 1)
        {
            GameLog::GetInstance()->PrintLogs();
        }
        else if (logChoice == 2)
        {
            GameLog::GetInstance()->PrintStatistics();
        }
		else if (logChoice == 3)
        {
            GameLog::GetInstance()->PrintAchievement();
        }
        else if (logChoice == 0)
        {
            break;
        }
        else
        {
            cout << RED << "잘못된 입력입니다." << RESET << endl;
        }
    }

    cout << GREEN << "게임이 종료되었습니다." << RESET << endl;
    return 0;
}
