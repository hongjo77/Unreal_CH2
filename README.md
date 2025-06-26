# 👾 용사 RPG - 보스까지 열걸음

C++ 콘솔창에서 진행되는 자동 턴제 텍스트 RPG입니다.

다양한 몬스터를 처치하며 성장하고, 최강의 보스 몬스터에 도전해보세요!

## ⚒️ 주요 기능

#### ◼ 캐릭터 생성 및 관리

- 원하는 이름과 함께 플레이어 캐릭터 생성
- 캐릭터의 주요 스탯 표시
- 레벨업 시 캐릭터의 체력, 공격력 증가
- 인벤토리로 아이템 저장

#### ◼ 전투 시스템

- 몬스터는 랜덤하게 출몰, 낮은 확률로 특수 몬스터 출몰
- 전투 중 아이템 사용이나 캐릭터 스킬 사용 등 자동 진행
- 전투 승리 시 고정적인 경험치 획득과 유동적인 골드 획득
- 몬스터 처치 시 낮은 확률로 아이템을 드랍
- 10레벨 달성 시 보스 몬스터 출몰

#### ◼ 상점 시스템

- 골드를 사용해 원하는 아이템과 수량을 자유롭게 구매 가능
- 인벤토리에 저장된 아이템을 수량을 정해서 판매 가능

## ➕ 추가 기능

#### ◼ 캐릭터 스킬 시스템

- 캐릭터에 마나 스탯 추가
- 마나가 있을 시 스킬 2종류와 일반 공격 중 랜덤으로 시전
- 일반 공격 시 마나 회복
- 스킬 공격 시 마나 소모 후 강력한 공격

#### ◼ 특수 몬스터

- 공격 시 플레이어 캐릭터의 골드 강탈
- 처치 시 강탈당한 골드와 더 많은 골드 획득
- 3턴 안에 못 잡을 시 도망

#### ◼ 보스 몬스터

- 공격 시 낮은 확률로 강력한 공격(스킬) 시전
- 공격 시 낮은 확률로 공격력 약화 or 방어도 약화 디버프 시전
- 처치 시 게임 엔딩!!

#### ◼ 장비 시스템

- 무기 장비를 통해 공격력 상승
- 방어구 장비를 통해 방어도 상승
- 상점에서 장비를 강화하는 대장장이 기능 추가
- 강화 성공은 확률이 존재하며 실패 시 강화 수치 유지 or 하락

#### ◼ 업적 시스템

- 플레이어는 주어진 조건을 만족하면 히든 업적 달성
- 게임 오버 시 로그, 통계, 업적 확인 가능

#### ◼ ASCII Art


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
