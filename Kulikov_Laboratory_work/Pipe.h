#pragma once
#include <unordered_map>
#include <iostream>
using namespace std;


class Pipe
{
private:
	double _PipeLength; // Длина трубы
	double _PipeDia;   //  Диаметр трубы
	bool _PipeStatus; //   Статус трубы (в ремонте или нет)
	string _PipeName;
	static int _PipeID;
public:
	Pipe();

	void Set(string PipeName, double PipeLength, double PipeDia, bool PipeStatus);
	void Set();
	void SetStatus(bool PipeStatus);
	double GetPipeLength() const;
	double GetPipeDia() const;
	bool GetPipeStatus() const;
	string GetPipeName() const;
	void Get() const;
	static int GetPipeID();

	void InputPipeStatusCheck();
	static void IDreplacement(const unordered_map<int, Pipe>& MapP);
	friend ifstream& operator>>(ifstream& fin, Pipe& p);
};

