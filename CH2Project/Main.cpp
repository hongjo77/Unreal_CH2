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
    cout << "ĳ���� �̸��� �Է��ϼ���: ";
    getline(cin, Name);

    // ĳ���� �ν��Ͻ� ����
    Characters* player = Characters::GetInstance(Name);
    GameManager manager;

    // �÷��̾ ���� �ʰų� 10������ ���� �ȵ� ���
    while (player->GetHealth() > 0 && player->GetLevel() < 10)
    {
        // �������ͽ� ���
        system("cls");
        player->DisplayStatus();
        cout << endl;

        // �� ����
        Monster* enemy = manager.GenerateMonster(player->GetLevel());
        // ���� ����
        manager.Battle(*player, *enemy);
        delete enemy;

        // �÷��̾� ���
        if (player->GetHealth() <= 0)
        {
            break;
        }
        // ���� �湮
        manager.VisitShop(*player);
    }

    // 10�����̸� ������ ����
    if (player->GetLevel() >= 10)
    {
        system("cls");
        player->DisplayStatus();
        cout << endl;

        // ���� ����
        BossMonster* boss = manager.GenerateBossMonster(player->GetLevel());
        // ���� ����
        manager.Battle(*player, *boss);
        delete boss;
    }

    cout << "������ ����Ǿ����ϴ�." << endl;
    return 0;
}
