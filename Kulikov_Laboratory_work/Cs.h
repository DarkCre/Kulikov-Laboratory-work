#pragma once
#include <string>
using namespace std;

class Cs
{
private:
	string _CsName; //название КС
	int _CsWorkshop; //количество цехов КС
	int _CsWorkingWorkshops; //количество работающих цехов КС
	int _CsEffectiveness; //эффективность КС
public:
	Cs();

	void Set(string CsName, int CsWorkshop, int CsWorkingWorkshops, int CsEffectiveness);
	void Set();

	string GetCsName() const;
	int GetCsWorkshop() const;
	int GetCsWorkingWorkshops() const;
	int GetCsEffectiveness() const;
	void Get() const;

	bool StartWorkshop();
	bool StopWorkshop();
};
