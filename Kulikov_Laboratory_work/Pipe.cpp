#include "Pipe.h"
#include <iostream>
#include "Checking.h"

int Pipe::_PipeID = 0;

void Pipe::InputPipeStatusCheck()
{
	//���������� ������� �����
	cout << "������� ������ ����� (� ������� - 0, � ��������������� ��������� - 1): " << endl;
	_PipeStatus = EnteringCheckingBool();
}

void Pipe::Set(double PipeLength, double PipeDia, bool PipeStatus)
{
	_PipeLength = PipeLength;
	_PipeDia = PipeDia;
	_PipeStatus = PipeStatus;
}

void  Pipe::Set()
{
	cout << "1.�������� �����:" << endl << endl;
	do//���������� ����� �����
	{
		cout << "������� ����� ����� (0.00):" << endl;
		cin >> _PipeLength;
	} while (!�heckingValues(_PipeLength, cin, 0.));
	do//���������� �������� �����
	{
		cout << "������� ������� ����� (0.00):" << endl;
		cin >> _PipeDia;
	} while (!�heckingValues(_PipeDia, cin, 0.));

	cout << "������� ������ ����� (� ������� - 0, � ��������������� ��������� - 1): " << endl;
	_PipeStatus=EnteringCheckingBool();
}

void Pipe::Get() const
{
	cout << endl << "����� �����: " << _PipeLength << endl
		<< "������� �����: " << _PipeDia << endl
		<< "������ �����: " << (_PipeStatus ? "� ������" : "� �������") << endl;
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

int Pipe::GetPipeID() const
{
	return _PipeID;
}

Pipe::Pipe()
{
	_PipeLength = 0;
	_PipeDia = 0;
	_PipeStatus = 0;
	++_PipeID;
}

