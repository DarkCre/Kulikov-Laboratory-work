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
	cout << "2.�������� ������������� �������: " << endl << endl;
	//���������� ����� ��
	cout << "������� �������� ������������� ������� (�� ��������� �����):" << endl;
	cin >> ws;
	getline(cin, _CsName);
	do//���������� ���������� ����� ��
	{
		cout << "������� ���������� ����� ������������� ������� (�����, ������������� �����):" << endl;
		cin >> _CsWorkshop;
	} while (!�heckingValues(_CsWorkshop, cin, 0));
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

void Cs::Get() const
{
	cout << "��������: " << _CsName << endl
		<< "���������� �����: " << _CsWorkshop << endl
		<< "���������� ����� � ������: " << _CsWorkingWorkshops << endl
		<< "�������������: " << _CsEffectiveness << endl;
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
		cout << "���������� ��������� � ������ ������ �����, ��� ����������. ����������, ��������� ������� �����." << endl;
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