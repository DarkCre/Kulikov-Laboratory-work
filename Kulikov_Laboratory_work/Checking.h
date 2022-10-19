#pragma once
#include <iostream>
using namespace std;

template <typename T>
bool �heckingValues(const T& Variable, istream& in = cin, T beginning = numeric_limits<T>::min(), T end = numeric_limits<T>::max())
{
	if (in.fail() || in.peek() != '\n' || Variable<beginning || Variable>end)
	{
		in.clear();
		in.ignore(1000, '\n');
		cout << "������� ����������� ������, ����������, ������� ����� �� " << beginning << " �� " << end << endl << endl;
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

bool EnteringCheckingBool();
