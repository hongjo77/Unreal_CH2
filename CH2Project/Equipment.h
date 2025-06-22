#pragma once
#include <string> 
using namespace std;

class Equipment
{
protected:
	//장비명
	string Name;
	//강화수치
	int EnhancementLevel;
	//장비스텟
	int Stat;
public:
	//장비 생성자
	Equipment(const string& name, int enLevel, int stat) : Name(name), EnhancementLevel(enLevel), Stat(stat) {}
	//장비 소멸자
	virtual ~Equipment() {}
	//Getter Setter
	virtual string GetName() const { return Name; }
	virtual int SetEnLevel(int newEnLevel) { EnhancementLevel = newEnLevel; }
	virtual int GetEnLevel() { return EnhancementLevel; }
	virtual int SetStat(int newStat) { Stat = newStat; }
	virtual int GetStat() { return Stat; }
};
