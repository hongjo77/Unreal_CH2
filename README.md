# 👾 텍스트 기반 RPG 게임 제작 프로젝트
C++ 콘솔창에서 진행되는 자동 턴제 RPG입니다.

다양한 몬스터를 처치하며 성장하고, 최강의 보스 몬스터에 도전해보세요!

## ⚒️ 주요 기능
#### 캐릭터 생성 및 관리
  - 원하는 이름과 함께 플레이어 캐릭터 생성
  - 캐릭터의 주요 스탯 표시
  - 레벨업 시 캐릭터의 체력, 공격력 증가
#### 전투 시스템
  - 몬스터는 랜덤하게 출몰, 낮은 확률로 특수 몬스터 출몰
  - 전투 중 아이템 사용이나 캐릭터 스킬 사용 등 자동 진행
  - 전투 승리 시 고정적인 경험치 획득과 유동적인 골드 획득
  - 몬스터 처치 시 낮은 확률로 아이템을 드랍
  - 10레벨 달성 시 보스 몬스터 출몰
#### 특수 몬스터
  - 공격 시 플레이어 캐릭터의 골드 강탈
  - 처치 시 강탈당한 골드와 더 많은 골드 획득
  - 3턴 안에 못 잡을 시 도망
#### 보스 몬스터
  - 공격 시 낮은 확률로 강력한 공격(스킬) 시전
  - 공격 시 낮은 확률로 공격력 약화 or 방어도 약화 디버프 시전
  - 처치 시 게임 엔딩!!
#### 상점 시스템
  - 골드를 사용해 원하는 아이템과 수량을 자유롭게 구매 가능
  - 인벤토리에 저장된 아이템을 수량을 정해서 판매 가능
  - 플레이어 캐릭터의 장비를 강화하는 대장장이 기능 추가
#### 장비 시스템
  - 무기 장비를 통해 공격력 상승
  - 방어구 장비를 통해 방어도 상승
  - 상점에서 장비 강화 가능
  - 강화 성공은 확률이 존재하며 실패 시 강화 수치 유지 or 하락
#### 업적 시스템
  - 플레이어는 주어진 조건을 만족하면 히든 업적 달성
  - 게임 오버 시 로그, 통계, 업적 확인 가능


## ⏰ 개발 기간
- 25.06.20 ~ 25.06.26

## 🧑‍🤝‍🧑 멤버 구성
| 이름 | 역할 | Github 주소 |
| -- | -- | -- |
|홍승조|Main.cpp, GameLog 클래스, 베이스 코드 작성|[hongjo77](https://github.com/hongjo77)|
|이정재|GameManager(몬스터 생성, 전투 시스템, 상점 방문, 인벤토리 표시)|[prostruin](https://github.com/prostruin)|
|정윤호|Character(캐릭터 스탯 초기화, 인벤토리, 마나 및 스킬 구현)|[hakunamatata9909](https://github.com/hakunamatata9909)|
|조성민|Shop(아이템 구매/판매, 장비 강화 기능 구현)|[Jo-sm94](https://github.com/Jo-sm94)|
|최희윤|Monster 인터페이스 및 하위 클래스 구성|[Chy-on](https://github.com/Chy-on)|
|홍사빈|Item, Equipment 인터페이스 및 하위 클래스 구성|[dioon0000](https://github.com/dioon0000)|

## ⚙️ 기술 스택
<img src="https://img.shields.io/badge/c++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white"> <img src="https://img.shields.io/badge/git-F05032?style=for-the-badge&logo=git&logoColor=white"> <img src="https://img.shields.io/badge/github-181717?style=for-the-badge&logo=github&logoColor=white">

<img src="https://img.shields.io/badge/IDE-Visual_Studio-5C2D91?style=for-the-badge&logo=visualstudio&logoColor=white" alt="Visual Studio Badge">


