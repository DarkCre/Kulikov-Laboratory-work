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

void Pipe::SetStatus(bool PipeStatus)
{
	_PipeStatus = PipeStatus;
}

string Pipe::GetName() const
{
	return _PipeName;
};

double Pipe::GetLength() const
{
	return _PipeLength;
}

double Pipe::GetDia() const
{
	return _PipeDia;
}

bool Pipe::GetStatus() const
{
	return _PipeStatus;
}

int Pipe::GetID()
{
	return _PipeID;
}

void Pipe::Get() const
{
	cout<<"Название трубы: "<<_PipeName<<endl
		<< "Длина трубы: " << _PipeLength << endl
		<< "Диаметр трубы: " << _PipeDia << endl
		<< "Статус трубы: " << (_PipeStatus ? "В работе" : "В ремонте") << endl;
}

void Pipe::InputStatusCheck()
{
	//Считывание статуса трубы
	cout << "Введите статус трубы " << _PipeName << " (в ремонте - 0, в работоспособном состоянии - 1) : " << endl;
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