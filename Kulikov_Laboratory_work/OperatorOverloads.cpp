#include "OperatorOverloads.h"



//Перегрузка операторов
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
		cout << elem.second.first << "---" << MapP.at(elem.first).GetDia() << "---" << elem.second.second << endl;
	}
	return fout;
}
//Перегрузка оператора вывода 
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
//Перегрузка ifstream на считывание трубы из файла с проверкой
ifstream& operator>>(ifstream& fin, Pipe& p)
{
	fin >> ws;
	getline(fin, p._PipeName);

	fin >> p._PipeLength;
	fin >> p._PipeDia;
	fin >> p._PipeStatus;

	return fin;
}
//Перегрузка ifstream на считывание Cs из файла с проверкой
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


	{
		cout << "Введите:" << endl
			<< "1, если диаметр трубы = 500" << endl
			<< "2, если диаметр трубы = 700" << endl
			<< "3, если диаметр трубы = 1400" << endl;

		int item = IntInput(1, 3);

		switch (item)
		{
		case 1:
		{ p._PipeDia = 500;	break;}
		case 2:
		{ p._PipeDia = 700; break;}
		case 3:
		{ p._PipeDia = 1400; break;}
		}
	}
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


