#include "OperatorOverloads.h"




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
ostream& GraphOutput(ostream& fout, const unordered_map<int, pair <int, int>>& Graph, const  unordered_map<int, Pipe>& MapP)
{
	if (Graph.size() == 0)
	{
		cout << "���������� ������� ���� �� ���� ���������� ��!";
		return fout;
	}
	for (const auto& elem : Graph)
	{
		cout << elem.second.first << "---" << MapP.at(elem.first).GetDia() << "---" << elem.second.second << endl << ". ��� ����� � ID " << elem.first << endl;;
	}
	return fout;
}
ofstream& operator<<(ofstream& fout, const unordered_map<int, pair<int, int>>& Graph)
{
	for (const auto& elem : Graph)
	{
		fout <<  elem.first << endl << elem.second.first << endl << elem.second.second << endl<<endl;
	}
	return fout;
}
ofstream& operator<<(ofstream& fout, forward_list<int>& D)
{
	for (const auto& elem : D)
	{
		fout << elem << endl;
	}
	return fout;
}
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


ifstream& operator>>(ifstream& fin, Pipe& p)
{
	fin >> ws;
	getline(fin, p._PipeName);

	fin >> p._PipeLength;
	fin >> p._PipeDia;
	fin >> p._PipeStatus;

	return fin;
}
ifstream& operator>>(ifstream& fin, Cs& Cs)
{
	fin >> ws;
	getline(fin, Cs._CsName);

	fin >> Cs._CsWorkshop;
	fin >> Cs._CsWorkingWorkshops;
	fin >> Cs._CsEffectiveness;
	return fin;
}
ifstream& operator>>(ifstream& fin, unordered_map<int, pair<int, int>>& Graph)
{
	Graph.clear();
	int SizeGraph;
	int IDPipe;
	int IDBegin;
	int IDEnd;
	fin >> SizeGraph;
	while (SizeGraph > 0)
	{
		fin >> IDPipe;
		fin >> IDBegin;
		fin >> IDEnd;
		Graph.emplace(IDPipe, pair<int, int>(IDBegin, IDEnd));
		--SizeGraph;
	}
	return fin;
}
ifstream& operator>>(ifstream& fin, forward_list<int>& D)
{
	D.clear();
	int IDPipe;
	fin >> IDPipe;
	while (IDPipe != -1)
	{
		D.emplace_front(IDPipe);
		fin >> IDPipe;
	}
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
	do//���������� ����� �����
	{
		cout << "������� ������� ����� (0.00):" << endl;
		cin >> p._PipeDia;
	} while (!�heckingValues(p._PipeDia, cin, 0.0001));

	{
		cout << "������� ������ ����� (� ������� - 0, � ��������������� ��������� - 1): " << endl;
		p._PipeStatus = EnteringCheckingBool();

		return fin;
	}
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
	do//���������� ������������� ��
	{
		cout << "������� ������������� ������� (����� ����� �� -100 �� 100):" << endl;
		cin >> cs._CsEffectiveness;
	} while (!�heckingValues(cs._CsEffectiveness, cin, -100, 100));

	return fin;
}


