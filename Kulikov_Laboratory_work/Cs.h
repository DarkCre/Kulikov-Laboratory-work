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

	string GetName() const;
	int GetWorkshop() const;
	int GetWorkingWorkshops() const;

	//void EditingWorkshop();
	bool StartWorkshop();
	bool StopWorkshop();

	static int GetID();
	static void IDreplacement(const unordered_map<int, Cs>& MapCs);

	friend ifstream& operator>>(ifstream& fin, Cs& Cs);
	friend istream& operator>>(istream& fin, Cs& cs);
	friend ofstream& OutputObjectsFile (ofstream& fout, const Cs& Cs);
	friend ostream& operator<<(ostream& fout, const Cs& cs);
};
