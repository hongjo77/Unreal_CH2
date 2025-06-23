#pragma once
#include <string> 

class Equipment
{
protected:
	//장비명
	std::string Name;
	//강화수치
	int EnhancementLevel;
	//장비스텟
	int Stat;
public:
	//장비 생성자
	Equipment(const std::string& name, int enLevel, int stat) : Name(name), EnhancementLevel(enLevel), Stat(stat) {} 
	//장비 소멸자
	virtual ~Equipment() {}
	//Getter & Setter
	virtual std::string GetName() const { return Name; }
	virtual void SetEnLevel(int newEnLevel) { EnhancementLevel = newEnLevel; }
	virtual int GetEnLevel() { return EnhancementLevel; }
	virtual void SetStat(int newStat) { Stat = newStat; }
	virtual int GetStat() { return Stat; }
};
