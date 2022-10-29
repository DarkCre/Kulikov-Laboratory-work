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
	cout << "2.�������� ������������� �������: " << endl << endl;
	
	do//���������� ����� ��
	{
		cout << "������� �������� ������������� ������� (�� ��������� �����):" << endl;
		cin >> ws;
		getline(cin, _CsName);
	} while (!CheckingString(_CsName));
	do//���������� ���������� ����� ��
	{
		cout << "������� ���������� ����� ������������� ������� (�����, ������������� �����):" << endl;
		cin >> _CsWorkshop;
	} while (!�heckingValues(_CsWorkshop, cin, 1));
	do//���������� ���������� ������� ����� ��
	{
		cout << "������� ���������� ���������� ����� (�����, ������������� �����, ������� ������ ���������� �����):" << endl;
		cin >> _CsWorkingWorkshops;
	} while (!�heckingValues(_CsWorkingWorkshops, cin, 0, _CsWorkshop));
	do//���������� ������������� ��
	{
		cout << "������� ������������� ������� (����� ����� �� -100 �� 100):" << endl;
		cin >> _CsEffectiveness;
	} while (!�heckingValues(_CsEffectiveness, cin, -100, 100));
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
	cout << "�������� ��: " << _CsName << endl
		<< "���������� �����: " << _CsWorkshop << endl
		<< "���������� ����� � ������: " << _CsWorkingWorkshops << endl
		<< "�������������: " << _CsEffectiveness << endl;
}

void Cs::EditingWorkshop()
{
	cout << "��� �� " << _CsName << endl;
	cout << "�� ������ ������ �� " << _CsWorkshop << " ����� � ������: " << _CsWorkingWorkshops<< endl << endl;
	cout << "������� 1 - ��� ���������� ���������� ���������� ����� �� 1." << endl
		 << "������� 0 - ��� ���������� ���������� ���������� ����� �� 1." << endl;
	
	while (true)
	{
		int item;
		do
		{
			cin >> item;
		} while (!�heckingValues(item, cin, 0, 1));

		if (item == 1)
		{
			if (StartWorkshop())
			{
				cout << "������ ���������."<<endl;
				return;
			}
		}
		else
		{
			if (StopWorkshop())
			{
				cout << "������ ���������."<<endl;
				return;
			}
		}
	}
}

bool Cs::StartWorkshop()
{
	if (_CsWorkingWorkshops == _CsWorkshop)
	{
		cout << "���������� ��������� � ������ ������ �����, ��� ����������. ����������, ��������� ������� �����." << endl;
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
		cout << "���������� ����������� ������� ����, ��� ��� ������ ��� ����� � ������. ����������, ��������� ������� �����." << endl;
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