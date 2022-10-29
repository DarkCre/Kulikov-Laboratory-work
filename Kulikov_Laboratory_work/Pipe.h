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
	void Set();
	void SetStatus(bool PipeStatus);

	string GetName() const;
	double GetLength() const;
	double GetDia() const;
	bool GetStatus() const;
	static int GetID();
	void Get() const;

	void InputStatusCheck();



	static void IDreplacement(const unordered_map<int, Pipe>& MapP);
	
	friend ifstream& operator>>(ifstream& fin, Pipe& p);
};

