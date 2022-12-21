#include "OperatorOverloads.h"




ostream& operator<<(ostream& fout, const Pipe& p)
{
	cout << "Название трубы: " << p._PipeName << endl
		<< "Длина трубы: " << p._PipeLength << endl
		<< "Диаметр трубы: " << p._PipeDia << endl
		<< "Статус трубы: " << (p._PipeStatus ? "В работе" : "В ремонте") << endl;
	return fout;
}
ostream& operator<<(ostream& fout, const Cs& cs)
{
	cout << "Название Кс: " << cs._CsName << endl
		<< "Количество цехов: " << cs._CsWorkshop << endl
		<< "Количество цехов в работе: " << cs._CsWorkingWorkshops << endl
		<< "Эффективность: " << cs._CsEffectiveness << endl;
	return fout;
}
ostream& GraphOutput(ostream& fout, const unordered_map<int, pair <int, int>>& Graph, const  unordered_map<int, Pipe>& MapP)
{
	if (Graph.size() == 0)
	{
		cout << "Необходимо создать хотя бы одно соединение КС!";
		return fout;
	}
	for (const auto& elem : Graph)
	{
		cout << elem.second.first << "---" << MapP.at(elem.first).GetDia() << "---" << elem.second.second << endl << ". Для трубы с ID " << elem.first << endl;;
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
	cout << "1.Создание трубы:" << endl << endl;

	do//Считывание имени трубы
	{
		cout << "Введите название трубы (на латинском языке):" << endl;
		cin >> ws;
		getline(cin, p._PipeName);
	} while (!CheckingString(p._PipeName));
	do//Считывание длины трубы
	{
		cout << "Введите длину трубы (0.00):" << endl;
		cin >> p._PipeLength;
	} while (!СheckingValues(p._PipeLength, cin, 0.0001));
	do//Считывание длины трубы
	{
		cout << "Введите диаметр трубы (0.00):" << endl;
		cin >> p._PipeDia;
	} while (!СheckingValues(p._PipeDia, cin, 0.0001));

	{
		cout << "Введите статус трубы (в ремонте - 0, в работоспособном состоянии - 1): " << endl;
		p._PipeStatus = EnteringCheckingBool();

		return fin;
	}
}
istream& operator>>(istream& fin, Cs& cs)
{
	cout << "2.Создание компрессорной станции: " << endl << endl;

	do//Считывание имени КС
	{
		cout << "Введите название компрессорной станции (на латинском языке):" << endl;
		cin >> ws;
		getline(cin, cs._CsName);
	} while (!CheckingString(cs._CsName));
	do//Считывание количества цехов КС
	{
		cout << "Введите количество цехов компрессорной станции (Целое, положительное число):" << endl;
		cin >> cs._CsWorkshop;
	} while (!СheckingValues(cs._CsWorkshop, cin, 1));
	do//Считывание эффективности КС
	{
		cout << "Введите эффективность станции (Целое число от -100 до 100):" << endl;
		cin >> cs._CsEffectiveness;
	} while (!СheckingValues(cs._CsEffectiveness, cin, -100, 100));

	return fin;
}


