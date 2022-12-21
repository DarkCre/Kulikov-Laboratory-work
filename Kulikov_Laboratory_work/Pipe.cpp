#include "Pipe.h"
#include "Checking.h"
#include <string>

int Pipe::_PipeID = 0;

Pipe::Pipe()
{
	_PipeName = "NoName";
	_PipeLength = 0;
	_PipeDia = 0;
	_PipeStatus = 0;
	++_PipeID;
}

void Pipe::Set(string PipeName, double PipeLength, double PipeDia, bool PipeStatus)
{
	_PipeName = PipeName;
	_PipeLength = PipeLength;
	_PipeDia = PipeDia;
	_PipeStatus = PipeStatus;
}

void Pipe::SetStatus(bool PipeStatus)
{
	_PipeStatus = PipeStatus;
}

double Pipe::GetDia() const
{
	return _PipeDia;
}

double Pipe::GetLength() const
{
	return _PipeLength;
}
string Pipe::GetName() const
{
	return _PipeName;
};

bool Pipe::GetStatus() const
{
	return _PipeStatus;
}

int Pipe::GetID()
{
	return _PipeID;
}


void Pipe::InputStatusCheck()
{
	//—читывание статуса трубы
	cout << "¬ведите статус трубы " << _PipeName << " (в ремонте - 0, в работоспособном состо€нии - 1) : " << endl;
	_PipeStatus = EnteringCheckingBool();
}



void Pipe::IDreplacement(const unordered_map<int, Pipe>& MapP)
{
	int Max = 0;
	for (auto itr = MapP.begin(); itr != MapP.end(); ++itr)
	{
		if (itr->first > Max)
		{
			Max= itr->first;
		}
	}
	_PipeID = Max;
}