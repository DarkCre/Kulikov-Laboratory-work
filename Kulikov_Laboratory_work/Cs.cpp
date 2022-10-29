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

void Cs::Set()
{
	cout << "2.Создание компрессорной станции: " << endl << endl;
	
	do//Считывание имени КС
	{
		cout << "Введите название компрессорной станции (на латинском языке):" << endl;
		cin >> ws;
		getline(cin, _CsName);
	} while (!CheckingString(_CsName));
	do//Считывание количества цехов КС
	{
		cout << "Введите количество цехов компрессорной станции (Целое, положительное число):" << endl;
		cin >> _CsWorkshop;
	} while (!СheckingValues(_CsWorkshop, cin, 1));
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

int Cs::GetEffectiveness() const
{
	return _CsEffectiveness;
}

int Cs::GetID()
{
	return _CsID;
}

void Cs::Get() const
{
	cout << "Название Кс: " << _CsName << endl
		<< "Количество цехов: " << _CsWorkshop << endl
		<< "Количество цехов в работе: " << _CsWorkingWorkshops << endl
		<< "Эффективность: " << _CsEffectiveness << endl;
}

void Cs::EditingWorkshop()
{
	cout << "Для Кс " << _CsName << endl;
	cout << "На данный момент из " << _CsWorkshop << " цехов в работе: " << _CsWorkingWorkshops<< endl << endl;
	cout << "Введите 1 - для увеличения количества работающих цехов на 1." << endl
		 << "Введите 0 - для уменьшения количества работающих цехов на 1." << endl;
	
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
				cout << "Данные сохранены."<<endl;
				return;
			}
		}
		else
		{
			if (StopWorkshop())
			{
				cout << "Данные сохранены."<<endl;
				return;
			}
		}
	}
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
		cout << "Невозможно осуществить останов цеха, так как сейчас нет цехов в работе. Пожалуйста, повторите попытку ввода." << endl;
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