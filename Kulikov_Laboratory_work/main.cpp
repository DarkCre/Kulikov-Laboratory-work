#include <iostream> //подключаем библиотеку для работы с вводом и выводом (# - означает что это данные для ввода в препроцессор).
#include <conio.h> // необходима для задержки, до нажатия клавиши
#include <fstream>// ввод в файл и вывод из файла
#include <string>
#include <unordered_map>
#include "Pipe.h"
#include "Checking.h"
#include "Cs.h"
#include <unordered_set>

//указываем по умолчание стандартное пространство имён (std), для того, что бы не указывать перед элементами данного пространства откуда они.
using namespace std;

//Создание новой трубы
void CreatingPipe(unordered_map<int, Pipe>& MapP)
{
	Pipe p1;
	p1.Set();
	MapP.emplace(p1.GetPipeID(), p1);
}
//вывод труб по статусу
void OutputByStatus(const unordered_map<int, Pipe>& MapP)
{
	cout << "Введите 1, если статус искомых труб 'В работбе' или 0, если их статус 'В ремонте'" << endl;
	bool Status = EnteringCheckingBool();
	for (auto itr = MapP.begin(); itr != MapP.end(); ++itr)
	{
		if (itr->second.GetPipeStatus() == Status)
		{
			cout << "ID трубы: " << itr->first;
			itr->second.Get();
			cout << endl;
		}
	}
}

//Вывод информации по элементам
void InformationOutput(const unordered_map<int, Pipe>& MapP, unordered_set<int>& SetP, const Cs& cs) //вывод информации по трубе и КС
{

	cout<< "1. Вывести информацию по всем трубам" << endl
		<< "2. Поиск информации по перечню ID труб" << endl
		<< "3. Поиск информации по статусу трубы" << endl
		<< "4. Вывести информацию по всем КС" << endl
		<< "5. Поиск информации по названию КС" << endl
		<< "6. Поиск информации по проценту незадействованных цехов КС" << endl
		<< "7. Вывести информацию по всем объектам" << endl
		<< "0. Для возврата в главное меню." << endl << endl;

	int check;
	int ID;
	int item = -1;
	do { cin >> item; } while (СheckingValues(item, cin, 0,7) == false);
	
	if ((item == (1, 2, 3)) && MapP.size() == 0)
	{
		cout << "Чтобы вывести информацию по трубам, необходимо создать хотя бы одну трубу.";
		return;
	}

	switch (item)
	{
	case 1:
		for (auto itr = MapP.begin(); itr != MapP.end(); ++itr)
		{
			cout << "ID трубы: " << itr->first; 
			itr->second.Get();
			cout<< endl;
		}
		return;
	case 2:
		cout << "Введите через Enter ID искомых труб."<<endl<<"Для завершения ввода введите последнее ID повторно."<< endl;

		do
		{
			cin >> ID;
		} while (!СheckingValues(ID));
		while (true)
		{
			do
			{
				cin >> check;
			} while (!СheckingValues(ID));
			SetP.emplace(ID);
			if (check == ID)
				break;
			ID = check;
		}
		cout << endl;
		for (auto itr = SetP.begin(); itr != SetP.end(); ++itr)
		{
			const auto i = MapP.find(*itr);
			if (i == MapP.end()) 
			{
				cout << "Не найдено трубы с ID = " << (*itr)<<endl<<endl;

			}
			else
			{
				cout << "ID трубы: " << i->first;
				i->second.Get();
				cout << endl;
			}

		}
		return;
	case 3:
		OutputByStatus(MapP);
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
	
}

//Редактирование трубы ytn
void EditingPipe(Pipe& p) //редактирование трубы
{
		cout << endl << "4.Редактирование трубы:" << endl << endl;
		p.InputPipeStatusCheck();
		cout << endl << "Данные сохранены." << endl;
}

//Редактирование Кс 
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

	//перегрузка оператора вывода 
	ostream& operator<<(ostream& os, const Pipe& p)
	{
		os << p.GetPipeLength() << endl<< p.GetPipeDia() << endl << p.GetPipeStatus()<<endl;
		return os;
	}

	//Проверка на существование файла с подтверждением о перезаписи
	bool ConfirmationFileOverwriting(ostream& fout)
	{
		fout.seekp(0, ios::end);
		int size = fout.tellp();
		fout.seekp(0, ios::beg);// 0-Значение смещения относительно параметра.
		if (size != 0)
		{
			cout << "Сохранение с таким названием уже существует! Вы хотите перезаписать его?" << endl
				<< "Введите 1, чтобы продолжить, либо 0 для отмены." << endl;

			if (!EnteringCheckingBool())
			{
				return false;
			}
		}
	}

	//Вывод трубы и его ID в файл
	void OutputInFilePipe(ostream& fout, const unordered_map<int, Pipe>& MapP)
	{
		for (auto itr = MapP.begin(); itr != MapP.end(); ++itr)
		{
			fout << itr->first <<endl<< itr->second << endl;
		}
	}

	//Выбор способа сохранения
	void ChoosingSavingMethod(const unordered_map<int, Pipe>& MapP, const Cs& cs, ostream& fout)
	{
		int item;
		do
		{
			cout << "Введите 1 - для сохранения только труб." << endl
				<< "Введите 2 - для сохранения только КС." << endl
				<< "Введите 3 - для сохранения текущего состояния (КС и трубы)." << endl;
			cin >> item;
		} while (СheckingValues(item, cin, 1, 3) == false);

		switch (item)
		{
		case 1:
			fout << MapP.size()<<" "<<0<< endl;
			OutputInFilePipe(fout, MapP);
			return;
		case 2:
			fout << 0 << " " << "KC.size()" << endl;
			//OutputInFileKC
			return;
		case 3:
			fout << MapP.size() << " "<< "KC.size()" << endl;
			OutputInFilePipe(fout, MapP);
			//OutputInFileKC
			return;
		}
	}

//Вывод в файл 
void OutputInFile(const unordered_map<int,Pipe>& MapP, const Cs& cs)
{
	cout << "6.Сохранение в файл." << endl
		 <<endl<<"Введите имя файла в формате 'имя.txt'"<<endl;
	string way ="";
	cin >> way;
	way.insert(0, "./saves/");

	ofstream fout;
	fout.exceptions(ofstream::badbit | ofstream::failbit);
	//https://www.youtube.com/watch?v=jCW2wRoRi0U
	{
		try
		{
			fout.open(way, ios::app);

			if (!ConfirmationFileOverwriting(fout))
			{
				fout.close();
				return;
			}
			fout.close();
			try
			{
				fout.open(way, ios::out);
				ChoosingSavingMethod(MapP, cs, fout);
			}
			catch (const  ofstream::failure& ex)
			{
				cout << ex.what() << endl << ex.code() << endl << "Ошибка при открытии/создании файла" << endl;
			}

			fout.close();
			/*
			fout << p.GetPipeLength() << endl << p.GetPipeDia() << endl << p.GetPipeStatus() << endl;
			fout << cs.GetCsName() << endl << cs.GetCsWorkshop() << endl << cs.GetCsWorkingWorkshops() << endl << cs.GetCsEffectiveness() << endl;

			fout.close();
			cout << "Данные сохранены";
			*/
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
	//Считывание информации про трубу из файла
	bool ReadingInformationFile(ifstream& fin, unordered_map<int, Pipe>& MapP)
	{
		char check;
		double PipeLength = 0;
		double PipeDia = 0;
		bool PipeStatus = 0;
		int pipeID = 0;

		fin >> pipeID;
		if (!СheckingIfstream(fin, PipeLength, 0.)) 
		{ 
			cout<<"Для трубы c ID: "<<pipeID;
			OutputReadingError();
			return false;
		}
		if (!СheckingIfstream(fin, PipeDia, 0.)) 
		{
			cout << "Для трубы c ID: " << pipeID;
			OutputReadingError();
			return false;
		}
		fin >> check;
		if (СheckingValues(check, fin, '0', '1'))
		{
			if (check == '1') { PipeStatus = true; }
		}
		else
		{
			cout << "Для трубы c ID: " << pipeID<<endl;
			OutputReadingError();
			return false;
		}
		Pipe p1;
		p1.Set(PipeLength, PipeDia, PipeStatus);
		if (MapP.find(pipeID) != MapP.end()) { OutputReadingError(); return false; }
		MapP.emplace(pipeID, p1);
		

		return true;
	}
	//Считывание труб из файла
	void ReadingPipesFromFile(ifstream& fin, unordered_map<int, Pipe>& MapP, int& NumberPipes)
	{
		unordered_map<int, Pipe> MapP1;
		while (NumberPipes != 0)
		{
			if (!ReadingInformationFile(fin, MapP1))
				return;
			--NumberPipes;
		}
		Pipe::IDreplacement(MapP1);
		MapP.swap(MapP1);
	}

//Считывание из файла ytn
void ReadingFromFile(unordered_map<int, Pipe>& MapP, Cs& cs)
{
	cout << "7.Загрузка данных из файла." << endl 
		 << "Данное действие приведёт к перезаписи введёных данных (если они есть). Убедитесь, что они вам не нужны." << endl
		 << "Введите 1, чтобы продолжить, либо 0 для отмены загрузки." << endl;
	if (EnteringCheckingBool())
	{
		ifstream fin;
		fin.exceptions(ifstream::badbit | ifstream::failbit);
		
		int NumberPipes=0;
		int NumberCS = 0;
		string CsName = "No name";
		int CsWorkshop = 0;
		int CsWorkingWorkshops = 0;
		int CsEffectiveness = 0;

		cout << endl << "Введите имя файла в формате 'имя.txt'" << endl;
		string way = "";
		cin >> way;
		way.insert(0, "./saves/");

		try
		{
			fin.open(way, ios::app);
			fin.seekg(0, ios::end);
			int size = fin.tellg();
			fin.seekg(0, ios::beg);
			if (size == 0)
			{
				cout << "Файл пуст!";
				return;
			}
			fin >> NumberPipes;
			fin >> NumberCS;

			int item;
			do
			{
				cout << "Введите 1 - для считывания только труб." << endl
					 << "Введите 2 - для считывания только КС." << endl
					 << "Введите 3 - для считывания сохранённого состояния (КС и трубы)." << endl;
				cin >> item;
			} while (СheckingValues(item, cin, 1, 3) == false);

			switch (item)
			{
			case 1:
				if (NumberPipes == 0) 
				{
					cout<<"В файле нет нужных структур данных!";
					return;}
				ReadingPipesFromFile(fin, MapP, NumberPipes);
				return;
			case 2:
				
				//KC
				return;
			case 3:
				if (NumberPipes == 0) { OutputReadingError(); return; }
				ReadingPipesFromFile(fin, MapP, NumberPipes);
				//KC
				return;
			}
			
			/*
			
			*/
			//считывание данных
			/*
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
			*/
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
int MainSharedConsole(unordered_map<int, Pipe>& MapP, unordered_set<int>& SetP,Pipe& p,Cs& cs)
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
			InformationOutput(MapP, SetP,cs);
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
			OutputInFile(MapP, cs);
			PauseAndClearing();
			return true;
		case 7:
			ReadingFromFile(MapP, cs);
			PauseAndClearing();
			return true;
		case 0:
			cout << endl << "Вы хотите сохранить текущее состояние?" <<
				endl << "Введите 1 для сохранения или 0, для выхода из программы." << endl;
			if (EnteringCheckingBool()) { OutputInFile(MapP, cs);}
			return false;
	}
	
	return true;
}

//Точка входа в программу
int main() 
{
	setlocale(LC_ALL, "rus"); //Подключение руссофикатора
	unordered_map<int, Pipe> MapP;
	unordered_set<int> SetP;
	//MapP.swap(umap1); что меняем (на что меняем)
	//Создание структур
	Pipe p;
	Cs cs = {};
	//Запуск консоли
	do { cout << endl; TextSharedConsole();} while (MainSharedConsole(MapP,SetP,p, cs) != 0);
}