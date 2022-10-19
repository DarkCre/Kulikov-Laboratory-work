#include "Cs.h"
#include <iostream>
#include "Checking.h"


void Cs::Set(string CsName, int CsWorkshop, int CsWorkingWorkshops, int CsEffectiveness)
{
	_CsName = CsName;
	_CsWorkshop = CsWorkshop;
	_CsWorkingWorkshops = CsWorkingWorkshops;
	_CsEffectiveness = CsEffectiveness;
}

void Cs::Set()
{
	cout << "2.Создание компрессорной станции: " << endl << endl;
	//Считывание имени КС
	cout << "Введите название компрессорной станции (на латинском языке):" << endl;
	cin >> ws;
	getline(cin, _CsName);
	do//Считывание количества цехов КС
	{
		cout << "Введите количество цехов компрессорной станции (Целое, положительное число):" << endl;
		cin >> _CsWorkshop;
	} while (!СheckingValues(_CsWorkshop, cin, 0));
	do//Считывание количества рабочих цехов КС
	{
		cout << "Введите количество работающих цехов (Целое, положительное число, которое меньше количества цехов):" << endl;
		cin >> _CsWorkingWorkshops;
	} while (!СheckingValues(_CsWorkingWorkshops, cin, 0, _CsWorkshop));
	do//Считывание эффективности КС
	{
		cout << "Введите эффективность станции (Целое число от -100 до 100):" << endl;
		cin >> _CsEffectiveness;
	} while (!СheckingValues(_CsEffectiveness, cin, -100, 100));

}

void Cs::Get() const
{
	cout << "Название: " << _CsName << endl
		<< "Количество цехов: " << _CsWorkshop << endl
		<< "Количество цехов в работе: " << _CsWorkingWorkshops << endl
		<< "Эффективность: " << _CsEffectiveness << endl;
}

string Cs::GetCsName() const
{
	return _CsName;
}

int Cs::GetCsWorkshop() const
{
	return _CsWorkshop;
}

int Cs::GetCsWorkingWorkshops() const
{
	return _CsWorkingWorkshops;
}

int Cs::GetCsEffectiveness() const
{
	return _CsEffectiveness;
}

bool Cs::StartWorkshop()
{
	if (_CsWorkingWorkshops == _CsWorkshop)
	{
		cout << "Невозможно запустить в работу больше цехов, чем существует. Пожалуйста, повторите попытку ввода." << endl;
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
		cout << "Невозможно запустить в работу больше цехов, чем существует. Пожалуйста, повторите попытку ввода." << endl;
		return false;
	}
	else
	{
		--_CsWorkingWorkshops;
		return true;
	}
}

Cs::Cs()
{
	_CsName = "No name";
	_CsWorkshop = 0;
	_CsWorkingWorkshops = 0;
	_CsEffectiveness = 0;
}