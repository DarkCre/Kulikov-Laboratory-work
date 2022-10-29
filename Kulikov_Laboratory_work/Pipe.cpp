#include "Pipe.h"
#include "Checking.h"
#include <string>

int Pipe::_PipeID = 0;

void Pipe::InputPipeStatusCheck()
{
	//Считывание статуса трубы
	cout << "Введите статус трубы (в ремонте - 0, в работоспособном состоянии - 1): " << endl;
	_PipeStatus = EnteringCheckingBool();
}

void Pipe::Set(string PipeName, double PipeLength, double PipeDia, bool PipeStatus)
{
	_PipeLength = PipeLength;
	_PipeDia = PipeDia;
	_PipeStatus = PipeStatus;
	_PipeName = PipeName;
}

void  Pipe::Set()
{
	cout << "1.Создание трубы:" << endl << endl;

	do//Считывание имени трубы
	{
		cout << "Введите название трубы (на латинском языке):" << endl;
		cin >> ws;
		getline(cin, _PipeName);
	} while (!CheckingString(_PipeName));
	do//Считывание длины трубы
	{
		cout << "Введите длину трубы (0.00):" << endl;
		cin >> _PipeLength;
	} while (!СheckingValues(_PipeLength, cin, 0.0001));
	do//Считывание диаметра трубы
	{
		cout << "Введите диаметр трубы (0.00):" << endl;
		cin >> _PipeDia;
	} while (!СheckingValues(_PipeDia, cin, 0.0001));

	cout << "Введите статус трубы (в ремонте - 0, в работоспособном состоянии - 1): " << endl;
	_PipeStatus=EnteringCheckingBool();
}

void Pipe::Get() const
{
	cout<<"Название трубы: "<<_PipeName<<endl
		<< "Длина трубы: " << _PipeLength << endl
		<< "Диаметр трубы: " << _PipeDia << endl
		<< "Статус трубы: " << (_PipeStatus ? "В работе" : "В ремонте") << endl;
}

double Pipe::GetPipeLength() const
{
	return _PipeLength;
}

double Pipe::GetPipeDia() const
{
	return _PipeDia;
}

bool Pipe::GetPipeStatus() const
{
	return _PipeStatus;
}

int Pipe::GetPipeID()
{

	return _PipeID;
}

string Pipe::GetPipeName() const
{
	return _PipeName;
};

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

Pipe::Pipe()
{
	_PipeName = "NoName";
	_PipeLength = 0;
	_PipeDia = 0;
	_PipeStatus = 0;
	++_PipeID;
}

