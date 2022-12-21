#pragma once
#include <iostream>
#include <unordered_map>
#include "Pipe.h"
#include "Cs.h"
#include <conio.h>
#include <forward_list>
#include <set>
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

template<typename T>
bool CheckingAvailabilityID(const set<int>& IDCsGraph, int& ID, unordered_map<int, T>& cs)
{
	if (IDCsGraph.find(ID) == IDCsGraph.end())
	{
		cout << "������� ID �� ����������." << endl;
		return false;
	}
	return true;
}


template<typename T>
bool CheckingAvailabilityID(int ID, const unordered_map<int, T>& Obj, forward_list<int>& FreePipes)
{
	if (Obj.find(ID) == Obj.end())
	{
		cout << "������� ID �� ����������." << endl;
		return false;
	}
	for (const auto elem : FreePipes)
	{
		if (ID == elem)
		{
			return true;
		}
	}
	cout << "����� � ID "<<ID<<" ������������ � �����! �������������� ��� �������� �������� �� ��������" << endl;
	return false;
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

template<typename T>
void InputAndCheckingAvailabilityID(unordered_map<int, T>& Obj, int& ID, forward_list<int>& FreePipes)
{
	do
	{
		ID = IntInput(0, T::GetID());
		if (ID == 0)
			break;
		else if (CheckingAvailabilityID(ID, Obj,FreePipes))
			break;
	} while (true);
}
template<typename T>
void InputAndCheckingAvailabilityID(unordered_map<int, T>& Obj, int& ID)
{
	do
	{
		ID = IntInput(0, T::GetID());
		if (ID == 0)
			break;
		else if (CheckingAvailabilityID(ID, Obj))
			break;
	} while (true);
}

template<typename T>
void InputAndCheckingAvailabilityID(unordered_map<int, pair <int, int>>& Obj, int& ID, unordered_map<int, T>& pipe)
{
	do
	{
		ID = IntInput(0, T::GetID());
		if (ID == 0)
			break;
		else if (CheckingAvailabilityID(ID, Obj))
			break;
	} while (true);
}


template<typename T>
void InputAndCheckingAvailabilityID(const set<int>& IDCsGraph, int& ID, unordered_map<int, T>& cs)
{
	do
	{
		ID = IntInput(0, T::GetID());
		if (ID == 0)
			break;
		else
		{
			if (CheckingAvailabilityID( IDCsGraph,ID,cs))
				break;
		}
	} while (true);
}

bool CheckingFulfillmentConditionsToGraph(const unordered_map<int, Cs>& MapCs);

template<typename T>
void InputAndCheckingAvailabilityIDToGraph(unordered_map<int, T>& Obj, int& ID)
{
	do
	{
		ID = IntInput(1, T::GetID());
		if (CheckingAvailabilityID(ID, Obj))
			return;
	} while (true);
}

void PauseAndClearing();