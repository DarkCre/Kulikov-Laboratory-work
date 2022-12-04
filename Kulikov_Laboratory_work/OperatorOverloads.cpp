#include "OperatorOverloads.h"

//���������� ����������
ostream& operator<<(ostream& fout, const Pipe& p)
{
	cout << "�������� �����: " << p._PipeName << endl
		<< "����� �����: " << p._PipeLength << endl
		<< "������� �����: " << p._PipeDia << endl
		<< "������ �����: " << (p._PipeStatus ? "� ������" : "� �������") << endl;
	return fout;
}
ostream& operator<<(ostream& fout, const Cs& cs)
{
	cout << "�������� ��: " << cs._CsName << endl
		<< "���������� �����: " << cs._CsWorkshop << endl
		<< "���������� ����� � ������: " << cs._CsWorkingWorkshops << endl
		<< "�������������: " << cs._CsEffectiveness << endl;
	return fout;
}
//���������� ��������� ������ 
ofstream& OutputObjectsFile(ofstream& fout, const Pipe& p)
{
	fout << p._PipeName << endl << p._PipeLength << endl << p._PipeDia << endl << p._PipeStatus << endl;
	return fout;
}
ofstream& OutputObjectsFile(ofstream& fout, const Cs& Cs)
{
	fout << Cs._CsName << endl << Cs._CsWorkshop << endl << Cs._CsWorkingWorkshops << endl << Cs._CsEffectiveness << endl;
	return fout;
}
//���������� ifstream �� ���������� ����� �� ����� � ���������
ifstream& operator>>(ifstream& fin, Pipe& p)
{
	fin >> ws;
	getline(fin, p._PipeName);

	fin >> p._PipeLength;
	fin >> p._PipeDia;
	fin >> p._PipeStatus;

	return fin;
}
//���������� ifstream �� ���������� Cs �� ����� � ���������
ifstream& operator>>(ifstream& fin, Cs& Cs)
{
	fin >> ws;
	getline(fin, Cs._CsName);

	fin >> Cs._CsWorkshop;
	fin >> Cs._CsWorkingWorkshops;
	fin >> Cs._CsEffectiveness;
	return fin;
}
istream& operator>>(istream& fin, Pipe& p)
{
	cout << "1.�������� �����:" << endl << endl;

	do//���������� ����� �����
	{
		cout << "������� �������� ����� (�� ��������� �����):" << endl;
		cin >> ws;
		getline(cin, p._PipeName);
	} while (!CheckingString(p._PipeName));
	do//���������� ����� �����
	{
		cout << "������� ����� ����� (0.00):" << endl;
		cin >> p._PipeLength;
	} while (!�heckingValues(p._PipeLength, cin, 0.0001));
	do//���������� �������� �����
	{
		cout << "������� ������� ����� (0.00):" << endl;
		cin >> p._PipeDia;
	} while (!�heckingValues(p._PipeDia, cin, 0.0001));

	cout << "������� ������ ����� (� ������� - 0, � ��������������� ��������� - 1): " << endl;
	p._PipeStatus = EnteringCheckingBool();

	return fin;
}
istream& operator>>(istream& fin, Cs& cs)
{
	cout << "2.�������� ������������� �������: " << endl << endl;

	do//���������� ����� ��
	{
		cout << "������� �������� ������������� ������� (�� ��������� �����):" << endl;
		cin >> ws;
		getline(cin, cs._CsName);
	} while (!CheckingString(cs._CsName));
	do//���������� ���������� ����� ��
	{
		cout << "������� ���������� ����� ������������� ������� (�����, ������������� �����):" << endl;
		cin >> cs._CsWorkshop;
	} while (!�heckingValues(cs._CsWorkshop, cin, 1));
	do//���������� ���������� ������� ����� ��
	{
		cout << "������� ���������� ���������� ����� (�����, ������������� �����, ������� ������ ���������� �����):" << endl;
		cin >> cs._CsWorkingWorkshops;
	} while (!�heckingValues(cs._CsWorkingWorkshops, cin, 0, cs._CsWorkshop));
	do//���������� ������������� ��
	{
		cout << "������� ������������� ������� (����� ����� �� -100 �� 100):" << endl;
		cin >> cs._CsEffectiveness;
	} while (!�heckingValues(cs._CsEffectiveness, cin, -100, 100));

	return fin;
}

