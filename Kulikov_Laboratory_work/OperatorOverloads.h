#pragma once
#include "Pipe.h"
#include "Cs.h"
#include <iostream>
#include <fstream>
#include "Checking.h"
#include <string>


ifstream& operator>>(ifstream& fin, Cs& Cs);
istream& operator>>(istream& fin, Cs& cs);
ofstream& OutputObjectsFile(ofstream& fout, const Cs& Cs);
ostream& operator<<(ostream& fout, const Cs& cs);
ifstream& operator>>(ifstream& fin, Pipe& p);
istream& operator>>(istream& fin, Pipe& p);
ofstream& OutputObjectsFile(ofstream& fout, const Pipe& p);
ostream& operator<<(ostream& fout, const Pipe& p);

//Перегрузка оператора на вывод всего Map
template<typename T>
ostream& operator<<(ostream& os, const unordered_map<int, T>& Obj)
{
	int SizePipes = Obj.size();
	if (!CheckingPresenceElements(os, SizePipes)) { return os; }
	for (const auto& elem : Obj)
	{
		cout << "ID объекта: " << elem.first << endl << elem.second << endl;
	}
	return os;
}