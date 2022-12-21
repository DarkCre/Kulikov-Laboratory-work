#pragma once
#include <unordered_map>
#include <iostream>

using namespace std;

class Pipe
{
private:
	string _PipeName;
	double _PipeLength; // Длина трубы
	double _PipeDia;   //  Диаметр трубы
	bool _PipeStatus; //   Статус трубы (в ремонте или нет)
	static int _PipeID;
public:
	Pipe();

	void Set(string PipeName, double PipeLength, double PipeDia, bool PipeStatus);

	void SetStatus(bool PipeStatus);

	string GetName() const;
	bool GetStatus() const;
	double GetDia() const;
	double GetLength() const;

	void InputStatusCheck();

	
	static int GetID();
	static void IDreplacement(const unordered_map<int, Pipe>& MapP);



	friend ifstream& operator>>(ifstream& fin, Pipe& p);
	friend istream&  operator>>(istream& fin, Pipe& p);
	friend ofstream& OutputObjectsFile (ofstream& fout, const Pipe& p);
	friend ostream& operator<<(ostream& fout, const Pipe& p);
};

