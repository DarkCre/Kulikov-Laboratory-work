#include <iostream> //подключаем библиотеку для работы с вводом и выводом (# - означает что это данные для ввода в препроцессор).
#include <conio.h> // необходима для задержки, до нажатия клавиши
#include <fstream>// ввод в файл и вывод из файла
#include <string>
#include <unordered_map>
#include "Pipe.h"
#include "Checking.h"
#include "Cs.h"

//указываем по умолчание стандартное пространство имён (std), для того, что бы не указывать перед элементами данного пространства откуда они.
using namespace std;

//Создание новой трубы
void CreatingPipe(unordered_map<int, Pipe>& MapP)
{
	Pipe p1;
	p1.Set();
	MapP.emplace(p1.GetPipeID(), p1);
}

//Вывод информации по элементам ytn
void InformationOutput(const unordered_map<int, Pipe>& MapP, const Cs& cs) //вывод информации по трубе и КС
{

	cout<< "1. Вывести информацию по всем трубам" << endl
		<< "2. Поиск информации по перечню ID труб" << endl
		<< "3. Поиск информации по статусу трубы" << endl
		<< "4. Вывести информацию по всем КС" << endl
		<< "5. Поиск информации по названию КС" << endl
		<< "6. Поиск информации по проценту незадействованных цехов КС" << endl
		<< "7. Вывести информацию по всем объектам" << endl
		<< "0. Для возврата в главное меню." << endl << endl;


	int item = -1;
	do { cin >> item; } while (СheckingValues(item, cin, 0,7) == false);
	
	switch (item)
	{
	case 1:
		for (auto itr = MapP.begin(); itr != MapP.end(); itr++)
		{
			cout << "ID трубы: " << itr->first; 
			itr->second.Get();
			cout<< endl;
		}
		return;
	case 2:

		return;
	case 3:

		return;
	case 4:

		return;
	case 5:

		return;
	case 6:

		return;
	case 7:

		return;
	case 0:
		return;
	}

	return;
	

	cout << endl << "3.Информация по компрессорной станции:" << endl << endl;
	cs.Get();
}

//Редактирование трубы ytn
void EditingPipe(Pipe& p) //редактирование трубы
{
		cout << endl << "4.Редактирование трубы:" << endl << endl;
		p.InputPipeStatusCheck();
		cout << endl << "Данные сохранены." << endl;
}

//Редактирование Кс ytn
void EditingCs(Cs& cs) //диалоговая часть редактирования КС
{	
	int item;
	cout << endl << "5.Редактирование компрессорной станции:" << endl
		<< "На данный момент из "<< cs.GetCsWorkshop() << " цехов в работе: " << cs.GetCsWorkingWorkshops() << endl << endl;

	do
	{
		cout << "Введите 1 - для увеличения количества работающих цехов на 1." << endl
			<< "Введите 0 - для возврата в главное меню." << endl
			<< "Введите -1 - для уменьшения количества работающих цехов на 1." << endl;
		cin >> item;
	} while (СheckingValues(item, cin, -1, 1) == false);

	switch (item)
	{
	case 1:
		if (cs.StartWorkshop())
			cout << "Данные сохранены.";
		return;
	case 0:
		return;
	case -1:
		if (cs.StopWorkshop())
			cout << "Данные сохранены.";
		return;
	}
}

//Вывод в файл ytn
void OutputInFile(const Pipe& p, const Cs& cs)
{
	cout << "6.Сохранение в файл." << endl 
		 << "Данное действие приведёт к перезаписи файла data.txt."<<endl
		 << "Введите 1, чтобы продолжить, либо 0 для отмены." << endl;
	if (EnteringCheckingBool())
	{
		ofstream fout;
		fout.exceptions(ofstream::badbit | ofstream::failbit);
		//https://www.youtube.com/watch?v=jCW2wRoRi0U
		try
		{
			fout.open("data.txt", ios::out);

			fout << p.GetPipeLength() << endl << p.GetPipeDia() << endl << p.GetPipeStatus() << endl;
			fout << cs.GetCsName() << endl << cs.GetCsWorkshop() << endl << cs.GetCsWorkingWorkshops() << endl << cs.GetCsEffectiveness() << endl;
		
			fout.close();
			cout << "Данные сохранены";
		}
		catch (const  ofstream::failure& ex)
		{
			cout << ex.what() << endl << ex.code() << endl << "Ошибка при открытии/создании файла" << endl;
		}
	}
}

	//Вывод ошибки считывания файла
	void OutputReadingError()
	{
		cout << "Ошибка при чтении файла. В файле содержатся недопустимые значения" << endl;
	}

//Считывание из файла ytn
void ReadingFromFile(Pipe& p, Cs& cs)
{
	cout << "7.Загрузка данных из файла." << endl 
		 << "Данное действие приведёт к перезаписи введёных данных (если они есть). Убедитесь, что они вам не нужны." << endl
		 << "Введите 1, чтобы продолжить, либо 0 для отмены загрузки." << endl;
	if (EnteringCheckingBool())
	{
		ifstream fin;
		fin.exceptions(ifstream::badbit | ifstream::failbit);
		char check;

		double PipeLength = 0;
		double PipeDia = 0;
		bool PipeStatus = 0;
		string CsName = "No name";
		int CsWorkshop = 0;
		int CsWorkingWorkshops = 0;
		int CsEffectiveness = 0;
		try
		{
			fin.open("data.txt", ios::in);
			//считывание данных
			cout << "Длина трубы:" << endl;
			if (!СheckingIfstream(fin,PipeLength, 0.)) { OutputReadingError(); return; }
			cout << "Считано." << endl;
			cout << "Диаметр трубы:" << endl;
			if (!СheckingIfstream(fin, PipeDia, 0.)) { OutputReadingError(); return; }
			cout << "Считано." << endl;
			cout << "Статус трубы:" << endl;
			fin >> check;
			if (СheckingValues(check, fin, '0', '1'))
			{
				if (check == '1') { PipeStatus = true;}
			}
			else
			{
				OutputReadingError(); return;
			}
			cout << "Считано." << endl;
			cout << "Название КС:" << endl;
			fin>> ws;
			getline(fin, CsName);
			cout << "Считано." << endl;
			cout << "Количество цехов КС :" << endl;
			if (!СheckingIfstream(fin, CsWorkshop,0)) { OutputReadingError(); return;}
			cout << "Считано." << endl;
			cout << "Количество рабочих цехов:" << endl;
			if (!СheckingIfstream(fin, CsWorkingWorkshops,0,CsWorkshop)) { OutputReadingError(); return;}
			cout << "Считано." << endl;
			cout << "Эффективность КС" << endl;
			if (!СheckingIfstream(fin, CsEffectiveness,-100,100)) { OutputReadingError(); return;}
			cout << "Считано." << endl;

			fin.close();

			cout << endl << "Данные считаны." << endl;
			cs.Set(CsName, CsWorkshop, CsWorkingWorkshops, CsEffectiveness);
			p.Set(PipeLength, PipeDia, PipeStatus);
		}
		catch (const  ifstream::failure & ex)
		{ 
			cout << ex.what() << endl << ex.code() << endl << "Ошибка при открытии файла" << endl;
		}
	}
}

//Главная консоль
//Текст главной консоли
void TextSharedConsole() //текстовая часть консоли
	{
		cout << " Главное меню: " << endl
			<< "1. Добавить трубу" << endl
			<< "2. Добавить КС" << endl
			<< "3. Просмотр всех объектов" << endl
			<< "4. Редактировать трубу" << endl
			<< "5. Редактировать КС" << endl
			<< "6. Сохранить" << endl
			<< "7. Загрузить" << endl
			<< "0. Выход" << endl << endl;
	}
//Пауза
void PauseAndClearing()
{
	cout << endl << "Нажмите любую клавишу для возврата в главное меню." << endl;
	_getch();
	system("cls");
}

//Функциональная часть консоли
int MainSharedConsole(unordered_map<int, Pipe>& MapP,Pipe& p,Cs& cs) 
{
	int item =-1;
	do { cin >> item;} while (СheckingValues(item,cin, 0, 7) == false);


	switch (item)
	{
		case 1:
			CreatingPipe(MapP);
			PauseAndClearing();
			return true;
		case 2:
			cs.Set();
			PauseAndClearing();
			return true;
		case 3:
			InformationOutput(MapP, cs);
			PauseAndClearing();
			return true;
		case 4:
			EditingPipe(p);
			PauseAndClearing();
			return true;
		case 5:
			EditingCs(cs);
			PauseAndClearing();
			return true;
		case 6:
			OutputInFile(p, cs);
			PauseAndClearing();
			return true;
		case 7:
			ReadingFromFile(p, cs);
			PauseAndClearing();
			return true;
		case 0:
			cout << endl << "Вы хотите сохранить текущее состояние?" <<
				endl << "Введите 1 для сохранения или 0, для выхода из программы." << endl;
			if (EnteringCheckingBool()) { OutputInFile(p, cs);}
			return false;
	}
	
	return true;
}

//Точка входа в программу
int main() 
{
	setlocale(LC_ALL, "rus"); //Подключение руссофикатора
	unordered_map<int, Pipe> MapP;
	
	//Создание структур
	Pipe p;
	Cs cs = {};
	//Запуск консоли
	do { cout << endl; TextSharedConsole();} while (MainSharedConsole(MapP,p, cs) != 0);
}