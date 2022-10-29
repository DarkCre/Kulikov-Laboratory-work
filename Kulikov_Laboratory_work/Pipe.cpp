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
	cout << "1.�������� �����:" << endl << endl;

	do//���������� ����� �����
	{
		cout << "������� �������� ����� (�� ��������� �����):" << endl;
		cin >> ws;
		getline(cin, _PipeName);
	} while (!CheckingString(_PipeName));
	do//���������� ����� �����
	{
		cout << "������� ����� ����� (0.00):" << endl;
		cin >> _PipeLength;
	} while (!�heckingValues(_PipeLength, cin, 0.0001));
	do//���������� �������� �����
	{
		cout << "������� ������� ����� (0.00):" << endl;
		cin >> _PipeDia;
	} while (!�heckingValues(_PipeDia, cin, 0.0001));
	
	cout << "������� ������ ����� (� ������� - 0, � ��������������� ��������� - 1): " << endl;
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
	cout<<"�������� �����: "<<_PipeName<<endl
		<< "����� �����: " << _PipeLength << endl
		<< "������� �����: " << _PipeDia << endl
		<< "������ �����: " << (_PipeStatus ? "� ������" : "� �������") << endl;
}

void Pipe::InputStatusCheck()
{
	//���������� ������� �����
	cout << "������� ������ ����� " << _PipeName << " (� ������� - 0, � ��������������� ��������� - 1) : " << endl;
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