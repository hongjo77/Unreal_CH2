# 👾 용사 RPG - 보스까지 열걸음

C++ 콘솔창에서 진행되는 자동 턴제 텍스트 RPG입니다.

다양한 몬스터를 처치하며 성장하고, 최강의 보스 몬스터에 도전해보세요!

## ⚒️ 주요 기능

### ◼ 캐릭터 생성 및 관리

<details>
    <summary>원하는 이름과 함께 플레이어 캐릭터 생성</summary>

![image](https://github.com/user-attachments/assets/04b1baa6-6881-4e20-a4fc-77b9929fc221)
```c++
Characters::Characters(const string& inName)
	: Name(inName), Level(1), Health(200), MaxHealth(200), Attack(30), Experience(0), Gold(0), MaxMana(100),CurrentMana(100)
{
```

```c++
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
```
</details>
<details>
	<summary>캐릭터의 주요 스탯 표시</summary>

![image](https://github.com/user-attachments/assets/b2c0dd2e-00b6-4f20-a3b1-3072fe6884c2)

```c++
void Characters::DisplayStatus() const
{
	cout << "이름: " << Name << " | 레벨: " << Level << " | 체력: " << Health << "/" << MaxHealth << " | 방어력: " << GetTotalArmorStat()
	<< " | 공격력: (" << Attack <<" + "<<this->weapon->GetStat()<<")" << " | 경험치: " << Experience << " | 골드: " << Gold << endl;
}
```
</details>
<details>
	<summary>레벨업 시 캐릭터의 체력, 공격력 증가</summary>

![image](https://github.com/user-attachments/assets/2b16b62d-3eb9-4246-99f5-cc118f490972)
![image](https://github.com/user-attachments/assets/93864d1a-1398-4728-85c1-d0faa3ba8cdc)

```c++
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
```
</details>
<details>
	<summary>인벤토리로 아이템 저장</summary>

![image](https://github.com/user-attachments/assets/4697e35c-da7c-4a96-bcc1-278015829a4c)

```c++
Characters::Characters(const string& inName)
: Name(inName), Level(1), Health(200), MaxHealth(200), Attack(30), Experience(0), Gold(0), MaxMana(100),CurrentMana(100)
{
	this->InitEquipment();
	this->Inventory = {new HealthPotion(), new AttackBoost()};
	cout << "캐릭터 " << Name << " 생성 완료! 레벨: " << Level << ", 체력: " << Health << ", 공격력: " << Attack << endl;
	cout << endl;
}
```

```c++
// 체력포션 생성자 초기값 [ Name : Health Potion, Amount : 0 ]
HealthPotion::HealthPotion() : Item("Health Potion", 0) {}
```

```c++
//공격력 증가포션 생성자 Name : Attack Boost
AttackBoost::AttackBoost() : Item("Attack Boost", 0) {}
```
</details>


### ◼ 전투 시스템

<details>
	<summary>몬스터는 랜덤하게 출몰, 낮은 확률로 특수 몬스터 출몰</summary>

![image](https://github.com/user-attachments/assets/ed042ea1-6a41-4107-89d3-4a5ec190a025)

```c++
Monster* GameManager::GenerateMonster(int level) 
{
    int type = rand() % 10;
    switch (type)
    {
    case 0:
    case 1:
    case 2:
    case 3:
        return new Goblin(level);
    case 4:
    case 5:
    case 6: 
        return new Bat(level);
    case 7:
    case 8: 
        return new Slime(level);
    case 9: 
        return new GoldenGoblin(level);
    default: return new Goblin(level);
    }
}
```
</details>
<details>
	<summary>전투와 아이템 사용 자동 진행</summary>

![image](https://github.com/user-attachments/assets/b929222d-3a07-4abf-b5c2-188b5d5c6f72)

```c++
// 1. 아이템 사용
if (!player.GetInventory().empty())
{
	int useItemChance = rand() % 100;
	// 30% 확률
	if (useItemChance < 30)
	{
		// 가지고 있는 아이템 중 랜덤
		int itemIndex = rand() % player.GetInventory().size();
		// 아이템 사용
                player.GetInventory()[itemIndex]->Use(player);
	}
}
```
</details>
<details>
	<summary>전투 승리 시 고정적인 경험치 획득과 유동적인 골드 획득</summary>

![image](https://github.com/user-attachments/assets/ee7ee9a2-451b-403d-afe3-2c263842346f)

```c++
void Monster::OnDeath(Characters& player) {
    cout << endl;
    cout << Name << " 처치!" << endl;

    // 적을 물리쳤을 때 얻는 골드
    int goldReward = 10 + rand() % 11;
    // 플레이어 경험치 + 50 exp
    player.SetExperience(player.GetExperience() + 50);
    // 플레이어 골드 + 10~20 골드
    player.SetGold(player.GetGold() + goldReward);
    cout << player.GetName() << "가 50 EXP와 " << goldReward << " 골드를 획득했습니다. 현재 EXP: " 
        << player.GetExperience() << "/100, 골드: " << player.GetGold() << endl;
.
.
.
}
```
</details>
<details>
	<summary>몬스터 처치 시 낮은 확률로 아이템을 드랍</summary>

![image](https://github.com/user-attachments/assets/b73faf26-8113-448d-ab23-58890e9bd659)

```c++
void Monster::OnDeath(Characters& player) {
.
.
.
// 30% 확률로 아이템 드랍
    int dropChance = rand() % 100;
    if (dropChance < 30)
    {
        int index = DropItem();
        auto& playerInventory = player.GetInventory();
        playerInventory[index]->SetAmount(playerInventory[index]->GetAmount() + 1);
        cout << player.GetName() << "이(가) " << playerInventory[index]->GetName() << "을(를) 1개 획득했습니다!" << endl;
    }
}
```
```c++
// 몬스터가 아이템을 드랍
int Monster::DropItem() 
{
    int itemType = rand() % 2;
    if (itemType == 0)
    {
        cout << Name << "이(가) Health Potion을(를) 드랍했습니다!" << endl;
    }
    else
    {
        cout << Name << "이(가) Attack Boost을(를) 드랍했습니다!" << endl;
    }
    return itemType;
}
```
</details>
<details>
	<summary>10레벨 달성 시 보스 몬스터 출몰</summary>

![image](https://github.com/user-attachments/assets/994188b6-d06c-4d07-8533-94727d4cf15d)

```c++
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
```
</details>


### ◼ 상점 시스템

<details>
	<summary>골드를 사용해 원하는 아이템과 수량을 자유롭게 구매 가능</summary>


![image](https://github.com/user-attachments/assets/c76bc78d-aa61-4728-bcfa-d6ddcf30379a)
![image](https://github.com/user-attachments/assets/9b449255-e09b-4ca1-a9ba-86ce64c92a5c)

```c++
void Shop::BuyItem(int index, Characters& player)
{
    // 인덱스 확인
    if (index < 0 || index >= (int)AvailableItems.size())
    {
        cout << "잘못된 인덱스입니다." << endl;
        return;
    }

    string name = AvailableItems[index]->GetName();
    
    cout << name << "을(를) 선택하셨습니다. 구매 개수 선택 (0: 취소) : ";
    int count = 0;
    cin >> count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (count == 0) {
        cout << "아이템 구매를 취소하셨습니다.\n" << endl;
        return;
    }

    // 힐포션 선택하면 10원 아니면 (Attack boost인경우) 15원
    int price = (name == "Health Potion") ? 10 : 15;
    if (player.GetGold() < price * count)
    {
        cout << "골드가 부족합니다.\n" << endl;
        return;
    }
    
    auto& inv = player.GetInventory();
    inv[index]->SetAmount(inv[index]->GetAmount() + count);

    player.SetGold(player.GetGold() - (price * count));
    cout << inv[index]->GetName() << "을(를) "<< count << "개 구매했습니다!\n" << endl;
    GameLog::GetInstance()->GoldAchievement(-price);
    
}
```
</details>
<details>
	<summary>인벤토리에 저장된 아이템을 수량을 정해서 판매 가능</summary>

![image](https://github.com/user-attachments/assets/f4ce0329-3f63-4f48-a3ad-c272fe58d028)
![image](https://github.com/user-attachments/assets/2784c650-b2bd-42cf-8ef0-d93fd3e63515)

```c++
void Shop::SellItem(int index, Characters& player)
{
    auto& inv = player.GetInventory();
    // 인덱스 확인
    if (index < 0 || index >= (int)inv.size())
    {
        cout << "잘못된 인덱스입니다." << endl;
        return;
    }
    string name = inv[index]->GetName();
    cout << name << "을(를) 선택하셨습니다. (현재 소지 개수 : " << inv[index]->GetAmount() << ")" << endl;
    if (inv[index]->GetAmount() <= 0) {
        cout << "판매 할 수 있는 수량이 없습니다.\n" << endl;
        return;
    }

    while (true) {

        cout << "판매 개수 선택(0: 취소) : ";
        int count = 0;
        cin >> count;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (count == 0) {
            cout << "아이템 판매를 취소하셨습니다.\n" << endl;
            return;
        }

        // 힐포션 선택하면 10원 아니면 (Attack boost인경우) 15원
        int price = (name == "Health Potion") ? 10 : 15;
        // 원래 가격의 60%만 지급
        int sellPrice = static_cast<int>(price * 0.6);

        if (inv[index]->GetAmount() < count) {
            cout << "판매 가능한 개수를 넘었습니다.\n" << endl;
            continue;
        }

        player.SetGold(player.GetGold() + (sellPrice * count));
        cout << inv[index]->GetName() << "을(를) " << count << "개 판매했습니다. " << sellPrice * count << " 골드를 받았습니다.\n" << endl;

        inv[index]->SetAmount(inv[index]->GetAmount() - count);
        break;
    }
}
```
</details>



## ➕ 추가 기능

### ◼ 캐릭터 스킬 시스템

<details>
	<summary>캐릭터에 마나 스탯 추가</summary>

```c++
class Characters
{
private:
    static Characters* Instance;
    string Name;
    int Level;
    int Health;
    int MaxHealth;
    int Attack;
    int Experience;
    int Gold;
    int MaxMana; //최대 마나 추가
    int CurrentMana; //현재 마나 추가
```
</details>
<details>
	<summary>마나가 있을 시 스킬 2종류와 일반 공격 중 랜덤으로 시전</summary>

</details>
<details>
	<summary>일반 공격 시 마나 회복</summary>

</details>
<details>
	<summary>스킬 공격 시 마나 소모 후 강력한 공격</summary>

![image](https://github.com/user-attachments/assets/0007f663-dd05-46c8-8251-03678acdacdb)

```c++
int Characters::RandomAttack()
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
            CurrentMana -= 20;
            return Attack + 20;
        }
        else
        {
            recoverMana(10);
            this->currentAttackType = AttackType::Normal;
            return Attack;
        }
    
    case AttackType::FireBall:
        if (CurrentMana >= 50)
        {
            CurrentMana -= 50;
            return Attack + 40;
        }

        else
        {
            recoverMana(10);
            this->currentAttackType = AttackType::Normal;
            return Attack;
        }

    default:
        recoverMana(10);
        this->currentAttackType = AttackType::Normal;
        return Attack;
    }
}
```
```c++
std::ostringstream oss;

enemy.TakeDamage(player.RandomAttack());
if (player.GetAttackType() == AttackType::Normal)
{
	oss.str("");
	oss.clear();
	oss << player.GetName() << "이(가) " << enemy.GetName() << "를(을) 공격합니다." << endl;
	GameLog::GetInstance()->PrintAndLog(oss.str());
}
else if(player.GetAttackType()==AttackType::Strike)
{
	oss.str("");
	oss.clear();
	oss << player.GetName() << "이(가) " << enemy.GetName() << "에게 Strike를 사용합니다." << endl;
	GameLog::GetInstance()->PrintAndLog(oss.str());
}
else
{
	oss.str("");
	oss.clear();
	oss << player.GetName() << "이(가) " << enemy.GetName() << "에게 FireBall을 사용합니다." << endl;
	GameLog::GetInstance()->PrintAndLog(oss.str());
}
oss.str("");
oss.clear();
```
</details>


### ◼ 특수 몬스터

<details>
	<summary>공격 시 플레이어 캐릭터의 골드 강탈</summary>

![image](https://github.com/user-attachments/assets/97b4424e-23c1-4ccf-9738-49744534fdaa)

```c++
void GoldenGoblin::AttackPlayer(Characters& player) 
{
	int prevPlayerHealth = player.GetHealth();
	int ArmorSubAttack = 0;
	if (player.GetTotalArmorStat() - Attack > 0) {
		ArmorSubAttack = 0;
	}
	else {
		ArmorSubAttack = player.GetTotalArmorStat() - Attack;
	}
	int newHealth = prevPlayerHealth + ArmorSubAttack;
	int prevGold = player.GetGold();
	if (prevGold > 0) 
	{
		int newGold = prevGold - GoldAttack;
		StolenMoney += GoldAttack;
		if (newGold < 0) { newGold = 0; }
		player.SetGold(newGold);
	}

	if (newHealth < 0) { newHealth = 0; }
	player.SetHealth(newHealth);
	cout << Name << "이(가) " << player.GetName() << "를 공격합니다! "
		<< player.GetName() << " 체력: " << prevPlayerHealth << " → " << player.GetHealth();
	if (prevGold > 0) 
	{
		cout << " 골드: " << prevGold << " -> " << player.GetGold() << endl;
	}
	else 
	{
		cout << " 골드: "<< player.GetGold() << endl;
	}
	cout << endl;
	// 로그 추가
	GameLog::GetInstance()->TakeDamageAchievement(-ArmorSubAttack);
}
```
</details>
<details>
	<summary>처치 시 강탈당한 골드와 더 많은 골드 획득</summary>

![image](https://github.com/user-attachments/assets/73150ca5-10a4-45d5-8fa7-4ed1b3af75b0)

```c++
void GoldenGoblin::OnDeath(Characters& player) 
{
	cout << endl;
	cout << Name << " 처치!" << endl;

	// 적을 물리쳤을 때 얻는 골드 (훔친 돈 포함)
	int goldReward = (100 + rand() % 100) + StolenMoney;
	// 플레이어 경험치 + 50 exp
	player.SetExperience(player.GetExperience() + 50);
	// 플레이어 골드 + 100~200 골드 + 훔친 돈
	player.SetGold(player.GetGold() + goldReward);
	cout << player.GetName() << "가 50 EXP와 " << goldReward << " 골드를 획득했습니다. 현재 EXP: "
		<< player.GetExperience() << "/100, 골드: " << player.GetGold() << endl;

	// 30% 확률로 아이템 드랍
	int dropChance = rand() % 100;
	if (dropChance < 30)
	{
		int index = DropItem();
		auto& playerInventory = player.GetInventory();
		playerInventory[index]->SetAmount(playerInventory[index]->GetAmount() + 1);
		cout << player.GetName() << "이(가) " << playerInventory[index]->GetName() << "을(를) 1개 획득했습니다!" << endl;
	}
	// 로그 추가
	GameLog::GetInstance()->GoldAchievement(goldReward);
}
```
</details>
<details>
	<summary>3턴 안에 못 잡을 시 도망</summary>

![image](https://github.com/user-attachments/assets/7b9b8b98-0330-4a4d-be3e-db6e6dbd4fbd)

```c++
if(enemy.IsGoldenGoblin() && BattleCount >= 4)
{
	oss.str("");
	oss.clear();
    oss << enemy.GetName() << "이(가) 전투에서 도망쳤습니다!" << endl;
	GameLog::GetInstance()->PrintAndLog(oss.str());
    enemy.TakeDamage(enemy.GetHealth()); //체력 0으로 만들어 죽은 상태로 처리

    //턴 초기화
    BattleCount = 1;
    break;
}
```
</details>


#### ◼ 보스 몬스터

<details>
	<summary>공격 시 낮은 확률로 강력한 공격(스킬) 시전</summary>


![image](https://github.com/user-attachments/assets/88f7045d-1a34-498c-a8e9-7b76b21fcd55)

```c++
//30% 확률로 스킬 공격
int skillChance = chanceDistribution(rng);
if (skillChance < 30)
{
	cout << Name << "이(가) 강력한 기술로 " << player.GetName() << "를 공격합니다! ";
        IsSkill = true;
        if (player.GetTotalArmorStat() - SkillAttack > 0) {
            ArmorSubAttack = 0;
        }
        else {
            ArmorSubAttack = player.GetTotalArmorStat() - SkillAttack;
        }
        newHealth = prevPlayerHealth + ArmorSubAttack;
}
else
{
        cout << Name << "이(가) " << player.GetName() << "를 공격합니다! ";
        if (player.GetTotalArmorStat() - Attack > 0) {
            ArmorSubAttack = 0;
        }
        else {
            ArmorSubAttack = player.GetTotalArmorStat() - Attack;
        }
        newHealth = prevPlayerHealth + ArmorSubAttack;
}

if (newHealth < 0)
{
        newHealth = 0;
}
player.SetHealth(newHealth);

cout<< player.GetName() << " 체력: " << prevPlayerHealth << " → " << player.GetHealth() << endl;

```
</details>
<details>
	<summary>공격 시 낮은 확률로 공격력 약화 or 방어도 약화 디버프 시전</summary>

```c++
// 일반 공격 시 각각 20% 확률로 공격력 감소, 방어력 감소 디버프
if (!IsSkill)
{
 	int debuffChance = chanceDistribution(rng);
        if (debuffChance >= 0 && debuffChance < 20)
        {
            int prevPlayerAttack = player.GetBaseAttack();
            int DroppedPlayerAttack = static_cast<int>(player.GetBaseAttack() * 0.8);
            player.SetAttack(DroppedPlayerAttack);

            cout << player.GetName() << "이(가) 공격력 감소 디버프에 걸렸습니다! "
                << player.GetName() << " 공격력: " << prevPlayerAttack << " → " << player.GetBaseAttack() << endl;
        }
        else if(debuffChance >=20 && debuffChance < 40)
        {
            int prevPlayerArmorStat = player.GetTotalArmorStat();
            auto EquipList = player.GetEquipments();
            for (auto& equip : EquipList) {
                if (equip->GetStat() > 0) {
                    equip->SetStat(equip->GetStat() - 5);
                }
                else {
                    equip->SetStat(0);
                }
            }
            cout << player.GetName() << "이(가) 방어력 감소 디버프에 걸렸습니다! "
                << player.GetName() << "방어력: " << prevPlayerArmorStat << " → " << player.GetTotalArmorStat() << endl;
        }
}
```
</details>
<details>
	<summary>처치 시 게임 엔딩!!</summary>

```c++

```
</details>


### ◼ 장비 시스템

<details>
	<summary>무기 장비를 통해 공격력 상승</summary>

```c++

```
</details>
<details>
	<summary>방어구 장비를 통해 방어도 상승</summary>

```c++

```
</details>
<details>
	<summary>상점에서 장비를 강화하는 대장장이 기능 추가</summary>

```c++

```
</details>
<details>
	<summary>강화 성공은 확률이 존재하며 실패 시 강화 수치 유지 or 하락</summary>

```c++

```
</details>


### ◼ 업적 시스템

<details>
	<summary>플레이어는 주어진 조건을 만족하면 히든 업적 달성</summary>

```c++

```
</details>
<details>
	<summary>게임 오버 시 로그, 통계, 업적 확인 가능</summary>

```c++

```
</details>

### ◼ ASCII Art


## ⏰ 개발 기간

- 25.06.20 ~ 25.06.26

## ⚙️ 개발 환경

- **IDE :** Visual Studio 2022
- **C++ 표준:** C++ 17 이상
- **encoding:** UTF-8

## 📚 자료 및 문서

- [기능명세서 페이지](https://teamsparta.notion.site/2182dc3ef51480f59a0ae5fb0ad2cc15?v=2182dc3ef51480d39847000cb7fca957)

- [클래스 목록 페이지](https://hongjo77.github.io/Unreal_CH2/html/annotated.html)

- [메인 흐름도](https://file.notion.so/f/f/83c75a39-3aba-4ba4-a792-7aefe4b07895/c01d560e-5078-4b20-883b-62fe64cc7eec/MainFlowChart.drawio.pdf?table=block&id=21e2dc3e-f514-805d-becd-ddf9fc6cb2ad&spaceId=83c75a39-3aba-4ba4-a792-7aefe4b07895&expirationTimestamp=1750968000000&signature=-Xe-VazbqJy7mFFNdMAts2rFEJPSLFC9DhpBrHrnbtY&downloadName=MainFlowChart.drawio.pdf)

- [전투 흐름도](https://file.notion.so/f/f/83c75a39-3aba-4ba4-a792-7aefe4b07895/de475ea7-f644-4502-9fa9-4a2e73b5f273/BattleFlowChart.drawio.pdf?table=block&id=21e2dc3e-f514-80e4-9799-f30a08ceb13b&spaceId=83c75a39-3aba-4ba4-a792-7aefe4b07895&expirationTimestamp=1750968000000&signature=h5RzPkQ7QKNxIJ7esQcGW_qsnmdatTXRWtiy6tiF1y4&downloadName=BattleFlowChart.drawio.pdf)

- [상점 흐름도](https://file.notion.so/f/f/83c75a39-3aba-4ba4-a792-7aefe4b07895/87efea06-4ec5-451e-bca0-c53c80f763fb/ShopFlowChart.drawio.pdf?table=block&id=21e2dc3e-f514-80a1-a897-deee0c912420&spaceId=83c75a39-3aba-4ba4-a792-7aefe4b07895&expirationTimestamp=1750968000000&signature=PlCF2AybWRIOA0F1oD_TovDOaY2HPgNX2VxgTv8QzNk&downloadName=ShopFlowChart.drawio.pdf)

- [클래스 다이어그램](https://file.notion.so/f/f/83c75a39-3aba-4ba4-a792-7aefe4b07895/ba0cca75-e6ed-458d-8718-0f922a13ba13/Unreal_CH2_5%EC%A1%B0_%EB%8B%A4%EC%9D%B4%EC%96%B4%EA%B7%B8%EB%9E%A8.pdf?table=block&id=21e2dc3e-f514-8072-a1d8-d19099b36a1e&spaceId=83c75a39-3aba-4ba4-a792-7aefe4b07895&expirationTimestamp=1750968000000&signature=Zxfd_onK7p0zVPCS9KNik8BsHl8VoBCbdKvVHVr7pcg&downloadName=Unreal_CH2_5%EC%A1%B0_%EB%8B%A4%EC%9D%B4%EC%96%B4%EA%B7%B8%EB%9E%A8.pdf)

## 📁 폴더 구조

```
CH2Project
| ┌ Item (Item.h)
| |  ├ AttackBoost (AttackBoost.h, AttackBoost.cpp)
| |  └ HealthPotion (HealthPotion.h, HealthPotion.cpp)
| |
│ ├ Monster (Monster.h, Monster.cpp)
| |  ├ Bat (Bat.h, Bat.cpp)
| |  ├ BossMonster (BossMonster.h, BossMonster.cpp)
| |  ├ Goblin (Goblin.h, Goblin.cpp)
| |  ├ GoldenGoblin (GoldenGoblin.h, GoldenGoblin.cpp)
| |  └ Slime (Slime.h, Slime.cpp)
| |
| ├ Characters (Characters.h, Characters.cpp)
| ├ GameLog (GameLog.h, GameLog.cpp)
| ├ GameManager (GameManager.h, GameManager.cpp)
| ├ Shop (Shop.h, Shop.cpp)
| |
│ ├ Equipment (Equipment.h)
| | ├ Weapon (Weapon.h, Weapon.cpp)
| | ├ Helmet (Helmet.h, Helmet.cpp)
| | ├ Chest (Chest.h, Chest.cpp)
| | └ Leg (Leg.h, Leg.cpp)
| |
│ ├ Color (Color.h)
│ └ Main.cpp
│
└ CH2Project.sln
```

## 🧑‍🤝‍🧑 멤버 구성

| 이름   | 역할                                                            | Github 주소                                             |
| ------ | --------------------------------------------------------------- | ------------------------------------------------------- |
| 홍승조 | Main.cpp, GameLog 클래스, 베이스 코드 작성                      | [hongjo77](https://github.com/hongjo77)                 |
| 이정재 | GameManager(몬스터 생성, 전투 시스템, 상점 방문, 인벤토리 표시) | [prostruin](https://github.com/prostruin)               |
| 정윤호 | Character(캐릭터 스탯 초기화, 인벤토리, 마나 및 스킬 구현)      | [hakunamatata9909](https://github.com/hakunamatata9909) |
| 조성민 | Shop(아이템 구매/판매, 장비 강화 기능 구현)                     | [Jo-sm94](https://github.com/Jo-sm94)                   |
| 최희윤 | Monster 인터페이스 및 하위 클래스 구성                          | [Chy-on](https://github.com/Chy-on)                     |
| 홍사빈 | Item, Equipment 인터페이스 및 하위 클래스 구성                  | [dioon0000](https://github.com/dioon0000)               |

## ✔️ 기술 스택

<img src="https://img.shields.io/badge/c++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white"> <img src="https://img.shields.io/badge/git-F05032?style=for-the-badge&logo=git&logoColor=white"> <img src="https://img.shields.io/badge/github-181717?style=for-the-badge&logo=github&logoColor=white">

## 🔗 관련 링크

- [팀 노션](https://teamsparta.notion.site/5-1ff2dc3ef5148096b38efc1cbaf5c14d)
