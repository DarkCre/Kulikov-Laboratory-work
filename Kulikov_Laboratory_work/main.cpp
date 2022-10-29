#include <iostream> //подключаем библиотеку для работы с вводом и выводом (# - означает что это данные для ввода в препроцессор).
#include <conio.h> // необходима для задержки, до нажатия клавиши
#include <fstream>// ввод в файл и вывод из файла
#include <string>
#include <unordered_map>
#include "Pipe.h"
#include "Checking.h"
#include "Cs.h"
#include <unordered_set>

//Указываем по умолчание стандартное пространство имён (std), для того, что бы не указывать перед элементами данного пространства откуда они.
using namespace std;
//Пауза
void PauseAndClearing()
{
	cout << endl << "Нажмите любую клавишу для возврата в главное меню." << endl;
	_getch();
	system("cls");
}

//Фильтр для проверки ошибок
template<typename T>
using FilterError = bool(*)(T& flow, int&);
//Проверка на наличие элементов в массиве
template<typename T>
bool CheckingPresenceElements(T& flow,int& size)
{
	if (size == 0)
	{
		cout << "Необходимо иметь хотя бы один элемент!" << endl;
		return false;
	}
	return true;
}
//Проверка значения количества элементов
bool CheckingNumberElements(ifstream& flow, int& Number)
{
	if (!СheckingIfstream(flow, Number, 0))
	{
		cout << "Количество элементов не может быть меньше 0!" << endl;
		return false;
	}
	return true;
}
//Проверка на то, что ID больше 0
bool CheckID(ifstream& flow, int& PipeID)
{
	if (!СheckingIfstream(flow, PipeID, 1))
	{
		cout << "ID не может быть меньше 0!" << endl;
		return false;
	}
	return true;
}

//Закрытие в файла в случае неудачной проверки  на наличие элементов в файле
template<typename T>
void CheckingErrorsInFile(T& flow, FilterError<T> f,int& param)
{
	if (!f(flow, param))
	{
		flow.close();
		flow.setstate(std::ios_base::failbit);
		return;
	}
}

/*
//Проверка на существование ID
bool CheckingAvailabilityID(int ID, const unordered_map<int, Pipe>& MapP)
{
	if (MapP.find(ID) == MapP.end())
	{
		cout << "Данного ID не существует.";
		return false;
	}
	return true;
}
*/

//Ввод Инта
int IntInput(int beginning, int end)
{
	int item;
	do
	{
		cin >> item;
	} while (СheckingValues(item, cin, beginning, end) == false);
	return item;
}
//Ввод фрагмента имени
string EnteringFragmentName()
{
	string Name = "NoName";
	do
	{
		cout << "Введите фрагмент названия искомых труб." << endl << "Фильтр: ";
		cin >> ws;
		getline(cin, Name);
	} while (!CheckingString(Name));
	return Name;
}
//Ввод имени файла
string EnteringFileName()
{
	cout << endl << "Введите имя файла: " << endl;
	string way = "";
	cin >> way;
	way.insert(0, "./saves/");
	way.append(".txt");
	return way;
}

//Фильтр для поиска
template<typename T>
using Filter = bool(*)(const Pipe& P, T param);
//Проверка подходит ли имя
bool CheckByName(const Pipe& P, string param)
{
	return  (P.GetPipeName().find(param) != string::npos);
}
//Проверка подходит ли статус
bool CheckByNameStatus(const Pipe& P, bool param)
{
	return(P.GetPipeStatus() == param);
}


//Создание новой трубы
void CreatingPipe(unordered_map<int, Pipe>& MapP)
{
	Pipe p1;
	p1.Set();
	MapP.emplace(p1.GetPipeID(), p1);
}


	//Перегрузка оператора на вывод всего Map
	ostream& operator<<(ostream& os, const unordered_map<int, Pipe>& MapP)
	{
		int SizePipes = MapP.size();
		if (!CheckingPresenceElements(os,SizePipes)) { return os;}
		for (const auto& elem : MapP)
		{
			cout << "ID трубы: " << elem.first<<endl;
			elem.second.Get();
			cout << endl;
		}
		return os;
	}
//Вывод информации по элементам
void InformationOutput(const unordered_map<int, Pipe>& MapP, const Cs& cs) //вывод информации по трубе и КС
{
	string Name = "NoName";
	bool Status = false;
	int SizePipes = MapP.size();
	cout<< "1. Вывести информацию по всем трубам" << endl
		<< "2. Вывести информацию по всем КС" << endl
		<< "3. Вывести информацию по всем объектам" << endl
		<< "0. Для возврата в главное меню." << endl << endl;

	int item = IntInput(0, 7);

	switch (item)
	{
	case 1:
		cout << MapP;
		return;
	case 2:

		return;
	case 3:

		return;
	case 0:
		return;
	}
	return;
	
}


void BatchEditingPipes(unordered_map<int, Pipe>& MapP, unordered_set<int>& SetP)
{
	cout << "Введите новый статус трубы (в ремонте - 0, в работоспособном состоянии - 1)" << endl;
	int Status = IntInput(0, 1);
	for (const auto& elem : SetP)
	{
		MapP.at(elem).SetStatus(Status);
	}
}

void BatchErasePipes(unordered_map<int, Pipe>& MapP, unordered_set<int>& SetP)
{
	for (const auto& elem : SetP)
	{
		MapP.erase(elem);
	}
}

template<typename T>
void FilterResults(unordered_map<int, Pipe>& MapP, unordered_map<int, int>& IDs, Filter<T> f, T param)
{
	int count = 0;
	for (const auto& elem : MapP)
	{
		if (f(elem.second, param))
		{
			++count;
			cout << "Номер в списке: " << count << endl;
			cout << "ID трубы: " << elem.first << endl;
			elem.second.Get();
			cout << endl;
			IDs.emplace(count, elem.first);
		}
	}
	if (count == 0)
	{
		cout << "Труб с таким названием не найдено!" << endl;
		return;
	}
}

void EnteringIDChange(unordered_map<int, int>& IDs, unordered_set<int>& SetP)
{
	int Number = 0;
	cout << "Введите -1 для того, что бы выбрать все выведенные объекты" << endl
		<< "Или введите через Enter номера из списка интересующих вас объектов." << endl
		<< "Для завершения ввода введите 0" << endl;

	Number = IntInput(-1, IDs.size());
	while (Number != 0 && Number != -1)
	{
		SetP.emplace(IDs.at(Number));
		Number = IntInput(0, IDs.size());
	}
	if (SetP.size() == 0) { return; }
}

	//Вывод труб по статусу или имени.
	template<typename T>
	void ChangingObjects( unordered_map<int, Pipe>& MapP, Filter<T> f, T param)
	{
		unordered_map<int, int> IDs;
		FilterResults(MapP, IDs, f, param);
		unordered_set<int> SetP;
		EnteringIDChange(IDs, SetP);
		

		cout <<endl<< "Введите 1 для редактирования объектов или 0 для удаления."<<endl;
		int item = IntInput(0, 1);
		switch (item)
		{
		case 1:
			BatchEditingPipes(MapP, SetP);
			return;
			/*
			for (const auto& elem : SetP)
			{
				MapP.at(elem).InputPipeStatusCheck();
			}
			return;
			*/
		case 0:
			BatchErasePipes(MapP, SetP);
			return;
		}

	}	
	//Изменение объектов
void ChangingObjects(unordered_map<int, Pipe>& MapP, Cs& cs)
{
	string Name = "NoName";
	bool Status = false;
	int SizePipes = MapP.size();
	cout<< "1. Редактирование по фильтру названия труб" << endl
		<< "2. Редактирование по фильтру статуса трубы" << endl
		<< "3. Редактирование по фильтру названия КС" << endl
		<< "4. Редактирование по фильтру процента незадействованных цехов КС" << endl
		<< "5. Редактирование по ID труб" << endl
		<< "6. Редактирование по ID КС" << endl
		<< "0. Для возврата в главное меню." << endl << endl;

	int item = IntInput(0, 6);

	switch (item)
	{
	case 1:

		if (!CheckingPresenceElements(cout, SizePipes)) { return; }
		cout << endl;

		Name = EnteringFragmentName();

		ChangingObjects(MapP, CheckByName, Name);
		return;

		/*
		cout << "Введите через Enter ID искомых труб."<<endl<<"Для завершения ввода введите последнее ID повторно."<< endl;
		do
		{
			do
			{
				ID = InputItemAndID(1, Pipe::GetPipeID());
			} while (CheckingAvailabilityID(ID,MapP));
			SetP.emplace(ID);
		} while (ID!=0);
		cout << endl;

		for (const auto& elem : SetP)
		{
			const auto i = MapP.find(elem);
			cout << "ID трубы: " << i->first;
				i->second.Get();
				cout << endl;
		}
		*/
	case 2:
		if (!CheckingPresenceElements(cout, SizePipes)) { return; }
		cout << endl;

		cout << "Введите 1, если статус искомых труб 'В работе' или 0, если их статус 'В ремонте'" << endl;
		Status = EnteringCheckingBool();

		ChangingObjects(MapP, CheckByNameStatus, Status);
		return;
	case 3:

		return;
	case 4:

		return;
	case 5:

		return;
	case 6:

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
	cout << endl << "5.Редактирование компрессорной станции:" << endl
		<< "На данный момент из "<< cs.GetCsWorkshop() << " цехов в работе: " << cs.GetCsWorkingWorkshops() << endl << endl;
	cout << "Введите 1 - для увеличения количества работающих цехов на 1." << endl
		<< "Введите 0 - для возврата в главное меню." << endl
		<< "Введите -1 - для уменьшения количества работающих цехов на 1." << endl;

	int item = IntInput(-1, 1);
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


	//Перегрузка оператора вывода 
	ofstream& operator<<(ofstream& os, const Pipe& p)
	{
		os << p.GetPipeName()<< endl<< p.GetPipeLength() << endl<< p.GetPipeDia() << endl << p.GetPipeStatus()<<endl;
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
	void OutputInFilePipe(ofstream& fout, const unordered_map<int, Pipe>& MapP)
	{
		for (auto itr = MapP.begin(); itr != MapP.end(); ++itr)
		{
			fout << itr->first << endl;
			fout << itr->second << endl;
		}
	}
	//Выбор способа сохранения
	void ChoosingSavingMethod(const unordered_map<int, Pipe>& MapP, const Cs& cs, ofstream& fout)
	{
		int SizePipes = MapP.size();
		CheckingErrorsInFile(fout, CheckingPresenceElements, SizePipes);
		cout << "Введите 1 - для сохранения только труб." << endl
			<< "Введите 2 - для сохранения только КС." << endl
			<< "Введите 3 - для сохранения текущего состояния (КС и трубы)." << endl;
		int item = IntInput(1, 3);

		switch (item)
		{
		case 1:
			fout << SizePipes <<endl<<0<< endl;
			OutputInFilePipe(fout, MapP);
			return;
		case 2:
			fout << 0 << endl << "KC.size()" << endl;
			//OutputInFileKC
			return;
		case 3:
			fout << MapP.size() << endl << "KC.size()" << endl;
			OutputInFilePipe(fout, MapP);
			//OutputInFileKC
			return;
		}
	}
//Вывод в файл 
void OutputInFile(const unordered_map<int,Pipe>& MapP, const Cs& cs)
{
	cout << "5.Сохранение в файл." << endl
		 <<endl<<"Введите имя файла"<<endl;
	string way = EnteringFileName();

	ofstream fout;
	fout.exceptions(ofstream::badbit | ofstream::failbit);
	//https://www.youtube.com/watch?v=jCW2wRoRi0U
	
	try
	{
		fout.open(way,  ios::app);

		if (!ConfirmationFileOverwriting(fout))
		{
			fout.close();
			return;
		}
		fout.close();
		fout.open(way);
		ChoosingSavingMethod(MapP, cs, fout);
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


	//Перегрузка ifstream на считывание трубы из файла с проверкой
	ifstream& operator>>(ifstream& fin, Pipe& p)
	{
		char check;
		fin >> ws;
		getline(fin, p._PipeName);
		if (CheckingString(p._PipeName) && СheckingIfstream(fin, p._PipeLength, 0.) && СheckingIfstream(fin, p._PipeDia, 0.))
		{
			fin >> check;
			if (СheckingValues(check, fin, '0', '1'))
			{
				if (check == '1') { p._PipeStatus = true; }
			}
			else
			{
				fin.setstate(std::ios_base::badbit);
			}
		}
		else
		{
			fin.setstate(std::ios_base::badbit);
		}
		return fin;
	}
	//Считывание информации про трубу из файла с проверкой
	bool ReadingInformationFile(ifstream& fin, unordered_map<int, Pipe>& MapP)
	{
		int PipeID = 0;
		CheckingErrorsInFile(fin, CheckID, PipeID);
		Pipe p1;
		fin >> p1;
		if ((MapP.find(PipeID) != MapP.end()) || fin.bad())
		{ 
			cout << "Для трубы c ID: " << PipeID << endl;
			cout << "Ошибка при чтении файла. В файле содержатся недопустимые значения" << endl;
			return false;
		}

		MapP.emplace(PipeID, p1);
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
	cout << "6.Загрузка данных из файла." << endl 
		 << "Данное действие приведёт к перезаписи введёных данных (если они есть). Убедитесь, что они вам не нужны." << endl
		 << "Введите 1, чтобы продолжить, либо 0 для отмены загрузки." << endl;
	if (EnteringCheckingBool())
	{
		ifstream fin;
		fin.exceptions(ifstream::failbit);
		int NumberPipes = 0;
		int NumberCS = 0;
		/*
		string CsName = "No name";
		int CsWorkshop = 0;
		int CsWorkingWorkshops = 0;
		int CsEffectiveness = 0;
		*/
		string way = EnteringFileName();

		try
		{
			fin.open(way, ios::in);
			CheckingErrorsInFile(fin, CheckingNumberElements, NumberPipes);
			CheckingErrorsInFile(fin, CheckingNumberElements, NumberCS);
			cout << "Введите 1 - для считывания только труб." << endl
				<< "Введите 2 - для считывания только КС." << endl
				<< "Введите 3 - для считывания сохранённого состояния (КС и трубы)." << endl;

			int item = IntInput(1, 3);

			switch (item)
			{
			case 1:
				CheckingErrorsInFile(fin, CheckingPresenceElements, NumberPipes);
				ReadingPipesFromFile(fin, MapP, NumberPipes);
				return;
			case 2:
				
				//KC
				return;
			case 3:
				CheckingErrorsInFile(fin, CheckingPresenceElements, NumberPipes);
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
			<< "4. Изменение объектов" << endl
			<< "5. Сохранить" << endl
			<< "6. Загрузить" << endl
			<< "0. Выход" << endl << endl;
	}

//Функциональная часть консоли
int MainSharedConsole(unordered_map<int, Pipe>& MapP,Cs& cs)
{
	int item = IntInput(0, 6);

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
			InformationOutput(MapP,cs);
			return true;
		case 4:
			ChangingObjects(MapP, cs);
			PauseAndClearing();
			/*
			EditingPipe(p);
			PauseAndClearing();
			return true;
			EditingCs(cs);
			PauseAndClearing();
			*/
			return true;
		case 5:
			OutputInFile(MapP, cs);
			PauseAndClearing();
			return true;
		case 6:
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
	//Создание структур
	Cs cs = {};
	//Запуск консоли
	do { cout << endl; TextSharedConsole();} while (MainSharedConsole(MapP,cs) != 0);
}