#pragma once
#include <iostream>
#include <unordered_map>
#include "Pipe.h"
#include "Cs.h"
using namespace std;

template <typename T>
bool СheckingValues(const T& Variable, istream& in = cin, T beginning = numeric_limits<T>::min(), T end = numeric_limits<T>::max())
{
	if (in.fail() || in.peek() != '\n' || Variable<beginning || Variable>end)
	{
		in.clear();
		in.ignore(1000, '\n');
		cout << "Óêàçàíû íåêîðåêòíûå äàííûå, ïîæàëóéñòà, óêàæèòå ÷èñëî îò " << beginning << " äî " << end << endl;
		return false;
	}
	return true;
}

template <typename T>
bool СheckingIfstream(ifstream& fin, T& Variable, T beginning = numeric_limits<T>::min(), T end = numeric_limits<T>::max())
{
	fin >> Variable;
	return ÑheckingValues(Variable, fin, beginning, end);
}


//Ïðîâåðêà íà ñóùåñòâîâàíèå ID
template<typename T>
bool CheckingAvailabilityID(int ID, const unordered_map<int, T>& Obj)
{
	if (Obj.find(ID) == Obj.end())
	{
		cout << "Äàííîãî ID íå ñóùåñòâóåò." << endl;
		return false;
	}
	return true;
}


//Ôèëüòð äëÿ ïîèñêà
template<typename T, typename T1>
using Filter = bool(*)(const T1&, T param);
//Ïðîâåðêà ïîäõîäèò ëè èìÿ
template<typename T>
bool CheckByName(const T& Obj, string param)
{
	return  (Obj.GetName().find(param) != string::npos);
}

//Ïðîâåðêà íà íàëè÷èå ýëåìåíòîâ â ìàññèâå 
template<typename T>
bool CheckingPresenceElements(T& flow, int& size)
{
	if (size == 0)
	{
		cout << "Íåîáõîäèìî èìåòü õîòÿ áû îäèí ýëåìåíò!" << endl;
		return false;
	}
	return true;
}
//Ïðîâåðêà ïî ýôôåêòèâíîñòè
bool CheckByEffectiveness(const Cs& Cs, double param);
//Ïðîâåðêà ïîäõîäèò ëè ñòàòóñ
bool CheckByStatus(const Pipe& P, bool param);

bool CheckingString(string S);

bool EnteringCheckingBool();

//Ââîä Èíòà
int IntInput(int beginning, int end);
