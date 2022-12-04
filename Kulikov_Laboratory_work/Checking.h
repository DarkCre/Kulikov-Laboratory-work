#pragma once
#include <iostream>
#include <unordered_map>
#include "Pipe.h"
#include "Cs.h"
using namespace std;

template <typename T>
bool �heckingValues(const T& Variable, istream& in = cin, T beginning = numeric_limits<T>::min(), T end = numeric_limits<T>::max())
{
	if (in.fail() || in.peek() != '\n' || Variable<beginning || Variable>end)
	{
		in.clear();
		in.ignore(1000, '\n');
		cout << "������� ����������� ������, ����������, ������� ����� �� " << beginning << " �� " << end << endl;
		return false;
	}
	return true;
}

template <typename T>
bool �heckingIfstream(ifstream& fin, T& Variable, T beginning = numeric_limits<T>::min(), T end = numeric_limits<T>::max())
{
	fin >> Variable;
	return �heckingValues(Variable, fin, beginning, end);
}


//�������� �� ������������� ID
template<typename T>
bool CheckingAvailabilityID(int ID, const unordered_map<int, T>& Obj)
{
	if (Obj.find(ID) == Obj.end())
	{
		cout << "������� ID �� ����������." << endl;
		return false;
	}
	return true;
}


//������ ��� ������
template<typename T, typename T1>
using Filter = bool(*)(const T1&, T param);
//�������� �������� �� ���
template<typename T>
bool CheckByName(const T& Obj, string param)
{
	return  (Obj.GetName().find(param) != string::npos);
}

//�������� �� �������������
bool CheckByEffectiveness(const Cs& Cs, double param);
//�������� �������� �� ������
bool CheckByStatus(const Pipe& P, bool param);


//�������� �� ������� ��������� � ������� 
template<typename T>
bool CheckingPresenceElements(T& flow, int& size)
{
	if (size == 0)
	{
		cout << "���������� ����� ���� �� ���� �������!" << endl;
		return false;
	}
	return true;
}


bool CheckingString(string S);

bool EnteringCheckingBool();

//���� ����
int IntInput(int beginning, int end);