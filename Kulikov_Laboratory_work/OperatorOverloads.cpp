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
	do//Считывание диаметра трубы
	{
		cout << "Введите диаметр трубы (0.00):" << endl;
		cin >> p._PipeDia;
	} while (!СheckingValues(p._PipeDia, cin, 0.0001));

	cout << "Введите статус трубы (в ремонте - 0, в работоспособном состоянии - 1): " << endl;
	p._PipeStatus = EnteringCheckingBool();

	return fin;
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
	do//Считывание количества рабочих цехов КС
	{
		cout << "Введите количество работающих цехов (Целое, положительное число, которое меньше количества цехов):" << endl;
		cin >> cs._CsWorkingWorkshops;
	} while (!СheckingValues(cs._CsWorkingWorkshops, cin, 0, cs._CsWorkshop));
	do//Считывание эффективности КС
	{
		cout << "Введите эффективность станции (Целое число от -100 до 100):" << endl;
		cin >> cs._CsEffectiveness;
	} while (!СheckingValues(cs._CsEffectiveness, cin, -100, 100));

	return fin;
}

