#pragma once
#include <iostream>
#include <fstream>
#include "Checking.h"
#include <string>
#include <forward_list>



istream& operator>>(istream& fin, Pipe& p);
istream& operator>>(istream& fin, Cs& cs);
ifstream& operator>>(ifstream& fin, Cs& Cs);
ifstream& operator>>(ifstream& fin, Pipe& p);
ifstream& operator>>(ifstream& fin, unordered_map<int, pair<int, int>>& Graph);
ifstream& operator>>(ifstream& fin, forward_list<int>& D);

ostream& operator<<(ostream& fout, const Pipe& p);
ostream& GraphOutput(ostream& fout, const unordered_map<int, pair <int, int>>& Graph, const  unordered_map<int, Pipe>& MapP);
ostream& operator<<(ostream& fout, const Cs& cs);
ofstream& OutputObjectsFile(ofstream& fout, const Cs& Cs);
ofstream& OutputObjectsFile(ofstream& fout, const Pipe& p);
ofstream& operator<<(ofstream& fout, forward_list<int>& D);
ofstream& operator<<(ofstream& fout, const unordered_map<int, pair<int, int>>& Graph);

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