#pragma once
#include <iostream>
using namespace std;

template <typename T>
bool ÑheckingValues(const T& Variable, istream& in = cin, T beginning = numeric_limits<T>::min(), T end = numeric_limits<T>::max())
{
	if (in.fail() || in.peek() != '\n' || Variable<beginning || Variable>end)
	{
		in.clear();
		in.ignore(1000, '\n');
		cout << "Óêàçàíû íåêîðåêòíûå äàííûå, ïîæàëóéñòà, óêàæèòå ÷èñëî îò " << beginning << " äî " << end << endl << endl;
		return false;
	}
	return true;
}

template <typename T>
bool ÑheckingIfstream(ifstream& fin, T& Variable, T beginning = numeric_limits<T>::min(), T end = numeric_limits<T>::max())
{
	fin >> Variable;
	return ÑheckingValues(Variable, fin, beginning, end);
}

bool EnteringCheckingBool();
