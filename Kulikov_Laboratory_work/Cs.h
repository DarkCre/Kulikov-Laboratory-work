#pragma once
#include <unordered_map>
#include <iostream>
using namespace std;


class Cs
{
private:
	string _CsName; //название КС
	int _CsWorkshop; //количество цехов КС
	int _CsWorkingWorkshops; //количество работающих цехов КС
	int _CsEffectiveness; //эффективность КС
	static int _CsID;
public:
	Cs();

	void Set(string CsName, int CsWorkshop, int CsWorkingWorkshops, int CsEffectiveness);
	void Set();


	string GetName() const;
	int GetWorkshop() const;
	int GetWorkingWorkshops() const;
	int GetEffectiveness() const;
	static int GetID();
	void Get() const;

	void EditingWorkshop();
	bool StartWorkshop();
	bool StopWorkshop();

	static void IDreplacement(const unordered_map<int, Cs>& MapCs);

	friend ifstream& operator>>(ifstream& fin, Cs& Cs);
};
