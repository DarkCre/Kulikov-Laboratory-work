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
		cout << "Указаны некоректные данные, пожалуйста, укажите число от " << beginning << " до " << end << endl;
		return false;
	}
	return true;
}

template <typename T>
bool СheckingIfstream(ifstream& fin, T& Variable, T beginning = numeric_limits<T>::min(), T end = numeric_limits<T>::max())
{
	fin >> Variable;
	return СheckingValues(Variable, fin, beginning, end);
}


//Проверка на существование ID
template<typename T>
bool CheckingAvailabilityID(int ID, const unordered_map<int, T>& Obj)
{
	if (Obj.find(ID) == Obj.end())
	{
		cout << "Данного ID не существует." << endl;
		return false;
	}
	return true;
}


//Фильтр для поиска
template<typename T, typename T1>
using Filter = bool(*)(const T1&, T param);
//Проверка подходит ли имя
template<typename T>
bool CheckByName(const T& Obj, string param)
{
	return  (Obj.GetName().find(param) != string::npos);
}

//Проверка по эффективности
bool CheckByEffectiveness(const Cs& Cs, double param);
//Проверка подходит ли статус
bool CheckByStatus(const Pipe& P, bool param);


//Проверка на наличие элементов в массиве 
template<typename T>
bool CheckingPresenceElements(T& flow, int& size)
{
	if (size == 0)
	{
		cout << "Необходимо иметь хотя бы один элемент!" << endl;
		return false;
	}
	return true;
}


bool CheckingString(string S);

bool EnteringCheckingBool();

//Ввод Инта
int IntInput(int beginning, int end);