#include "Cs.h"
#include "Checking.h"
#include <string>

int Cs::_CsID = 0;

Cs::Cs()
{
	_CsName = "No name";
	_CsWorkshop = 0;
	_CsWorkingWorkshops = 0;
	_CsEffectiveness = 0;
	++_CsID;
}

void Cs::Set(string CsName, int CsWorkshop, int CsWorkingWorkshops, int CsEffectiveness)
{
	_CsName = CsName;
	_CsWorkshop = CsWorkshop;
	_CsWorkingWorkshops = CsWorkingWorkshops;
	_CsEffectiveness = CsEffectiveness;
}

string Cs::GetName() const
{
	return _CsName;
}

int Cs::GetWorkshop() const
{
	return _CsWorkshop;
}

int Cs::GetWorkingWorkshops() const
{
	return _CsWorkingWorkshops;
}


int Cs::GetID()
{
	return _CsID;
}


void Cs::EditingWorkshop()
{
	cout << "Äëÿ Êñ " << _CsName << endl;
	cout << "Íà äàííûé ìîìåíò èç " << _CsWorkshop << " öåõîâ â ðàáîòå: " << _CsWorkingWorkshops<< endl << endl;
	cout << "Ââåäèòå 1 - äëÿ óâåëè÷åíèÿ êîëè÷åñòâà ðàáîòàþùèõ öåõîâ íà 1." << endl
		 << "Ââåäèòå 0 - äëÿ óìåíüøåíèÿ êîëè÷åñòâà ðàáîòàþùèõ öåõîâ íà 1." << endl;
	
	while (true)
	{
		int item;
		do
		{
			cin >> item;
		} while (!СheckingValues(item, cin, 0, 1));

		if (item == 1)
		{
			if (StartWorkshop())
			{
				cout << "Äàííûå ñîõðàíåíû."<<endl;
				return;
			}
		}
		else
		{
			if (StopWorkshop())
			{
				cout << "Äàííûå ñîõðàíåíû."<<endl;
				return;
			}
		}
	}
}

bool Cs::StartWorkshop()
{
	if (_CsWorkingWorkshops == _CsWorkshop)
	{
		cout << "Íåâîçìîæíî çàïóñòèòü â ðàáîòó áîëüøå öåõîâ, ÷åì ñóùåñòâóåò. Ïîæàëóéñòà, ïîâòîðèòå ïîïûòêó ââîäà." << endl;
		return false;
	}
	else
	{
		++_CsWorkingWorkshops;
		return true;
	}
}

bool Cs::StopWorkshop()
{
	if (_CsWorkingWorkshops == 0)
	{
		cout << "Íåâîçìîæíî îñóùåñòâèòü îñòàíîâ öåõà, òàê êàê ñåé÷àñ íåò öåõîâ â ðàáîòå. Ïîæàëóéñòà, ïîâòîðèòå ïîïûòêó ââîäà." << endl;
		return false;
	}
	else
	{
		--_CsWorkingWorkshops;
		return true;
	}
}

void Cs::IDreplacement(const unordered_map<int, Cs>& MapCs)
{
	int Max = 0;
	for (auto itr = MapCs.begin(); itr != MapCs.end(); ++itr)
	{
		if (itr->first > Max)
		{
			Max = itr->first;
		}
	}
	_CsID = Max;
}
