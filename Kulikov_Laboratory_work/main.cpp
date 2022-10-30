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
bool CheckID(ifstream& flow, int& ObjID)
{
	if (!СheckingIfstream(flow, ObjID, 1))
	{
		cout << "ID не может быть меньше 0!" << endl;
		return false;
	}
	return true;
}
//Проверка на существование ID
template<typename T>
bool CheckingAvailabilityID(int ID, const unordered_map<int, T>& Obj)
{
	if (Obj.find(ID) == Obj.end())
	{
		cout << "Данного ID не существует."<<endl;
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
	do
	{
		cin >> ws;
		getline(cin, way);
	} while (!CheckingString(way));
	way.insert(0, "./saves/");
	way.append(".txt");
	return way;
}

//Фильтр для поиска
template<typename T,typename T1>
using Filter = bool(*)(const T1& , T param);
//Проверка подходит ли имя
template<typename T>
bool CheckByName(const T& Obj, string param)
{
	return  (Obj.GetName().find(param) != string::npos);
}

//Проверка по эффективности
bool CheckByEffectiveness(const Cs& Cs, double param)
{
	double Workshop = Cs.GetWorkshop();
	double WorkingWorkshops = Cs.GetWorkingWorkshops();
	double Effectiveness = param / 100;
	return((1 - WorkingWorkshops / Workshop) >= Effectiveness);
}

//Проверка подходит ли статус
bool CheckByStatus(const Pipe& P, bool param)
{
	return(P.GetStatus() == param);
}

//Создание новой трубы
template<typename T>
void CreatingObject(unordered_map<int, T>& Obj)
{
	T obj;
	obj.Set();
	Obj.emplace(obj.GetID(), obj);
}

	template<typename T>
	void ChangingObjectsCs(unordered_map<int, Cs>& MapCs, Filter<T,Cs> f, T param)
	{
		unordered_map<int, int> IDs;
		FilterResults(MapCs, IDs, f, param);
	}
	//Перегрузка оператора на вывод всего Map
	template<typename T>
	ostream& operator<<(ostream& os, const unordered_map<int, T>& Obj)
	{
		int SizePipes = Obj.size();
		if (!CheckingPresenceElements(os,SizePipes)) { return os;}
		for (const auto& elem : Obj)
		{
			cout << "ID объекта: " << elem.first<<endl;
			elem.second.Get();
			cout << endl;
		}
		return os;
	}
//Вывод информации по элементам
void InformationOutput(const unordered_map<int, Pipe>& MapP,  unordered_map<int, Cs>& MapCs) //вывод информации по трубе и КС
{
	string Name = "NoName";
	double Effectiveness = 0;
	bool Status = false;
	int SizeCs = MapCs.size();
	cout<< "1. Вывести информацию по всем трубам" << endl
		<< "2. Вывести информацию по всем КС" << endl
		<< "3. Вывести информацию по всем объектам" << endl
		<< "4. Вывести информацию по фильтру название КС" << endl
		<< "5. Вывести информацию по фильтру процента незадействованных цехов КС" << endl
		<< "0. Для возврата в главное меню." << endl << endl;

	int item = IntInput(0, 7);

	switch (item)
	{
	case 1:
		cout <<"Трубы: "<<endl<< MapP;
		return;
	case 2:
		cout << "Компрессорные станции: " << endl << MapCs;
		return;
	case 3:
		cout << "Трубы: " << endl << MapP;
		cout << "Компрессорные станции: " << endl << MapCs;
		return;
	case 4:
		if (!CheckingPresenceElements(cout,SizeCs)) { return; }

		cout << endl;
		Name = EnteringFragmentName();

		ChangingObjectsCs(MapCs, CheckByName, Name);
		return;

	case 5:
		if (!CheckingPresenceElements(cout, SizeCs)) { return; }

		do
		{
			cout << "Введите процент незадействованных цехов (от 0 до 100): " << endl;
			cin >> Effectiveness;
		} while (!СheckingValues(Effectiveness, cin, 0., 100.));

		ChangingObjectsCs(MapCs, CheckByEffectiveness, Effectiveness);
		return;

		return;
	case 0:
		return;
	}
	return;
	
}
	
//Изменение объектов	
template<typename T>
			using FilterEditing = void(*)(T&, unordered_set<int>&);
			//Поэлементное редактирование списка труб
			void Element_By_ElementEditingPipe(unordered_map<int, Pipe>& MapP, unordered_set<int>& SetP)
			{
				for (const auto& elem : SetP)
				{
					MapP.at(elem).InputStatusCheck();
				}
			}
			void Element_By_ElementEditingCs(unordered_map<int, Cs>& MapCs, unordered_set<int>& SetP)
			{
				for (const auto& elem : SetP)
				{
					MapCs.at(elem).EditingWorkshop();
				}
			}

			//Пакетное редактирование статуса
			void BatchEditingPipes(unordered_map<int, Pipe>& MapP, unordered_set<int>& SetP)
			{
				cout << "Введите новый статус трубы (в ремонте - 0, в работоспособном состоянии - 1)" << endl;
				int Status = IntInput(0, 1);
				for (const auto& elem : SetP)
				{
					MapP.at(elem).SetStatus(Status);
				}
			}

			//Пакетное  удаление
			template<typename T>
			void BatchErasePipes(T& Obj, unordered_set<int>& SetP)
			{
				for (const auto& elem : SetP)
				{
					Obj.erase(elem);
				}
			}

		//Выбор действия с элементами
		template<typename T>
		void SelectingAnEditAction(T& Obj, unordered_set<int>& SetP, FilterEditing<T> f)
		{
			cout << endl << "Введите 1 для редактирования объектов или 0 для удаления." << endl;
			int item = IntInput(0, 1);
			switch (item)
			{
			case 1:
				f(Obj, SetP);
				return;
			case 0:
				BatchErasePipes(Obj, SetP);
				return;
			}
		}
	
		//Создание Set из всех элементов фильтра
		void SelectingAllFilterElements(unordered_map<int, int>& IDs, unordered_set<int>& SetP)
		{
			for (const auto& elem : IDs)
			{
				SetP.emplace(elem.second);
			}
		}
		//Что необходимо удалить или отредактировать 
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
			if (Number == 0 && SetP.size() == 0) { return; }
			if (Number == -1) { SelectingAllFilterElements(IDs, SetP); }
		}
		//Результаты фильтрации
		template<typename T,typename T1>
		void FilterResults(unordered_map<int, T1>& Obj, unordered_map<int, int>& IDs, Filter<T,T1> f, T param)
		{
			int count = 0;
			for (const auto& elem : Obj)
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
				cout << "Искомых объектов не найдено!" << endl;
				return;
			}
		}
		
		template<typename T>
		void InputAndCheckingAvailabilityID(unordered_map<int, T>& Obj,int& ID)
		{
			do
			{
				ID = IntInput(0, T::GetID());
				if (ID == 0)
					break;
				else if (CheckingAvailabilityID(ID, Obj))
					break;
			} while (true);
		}

		//Ввод ID для дальнейшего редактирования
		template<typename T>
		void InputSetP(unordered_map<int, T>& Obj, unordered_set<int>& SetP)
		{
			cout << "Введите через Enter ID объектов, которые нужно изменить." << endl
				<< "Для завершения ввода введите 0" << endl;
			int ID;
			InputAndCheckingAvailabilityID(Obj,  ID);
			while (ID != 0)
			{
				SetP.emplace(ID);
				InputAndCheckingAvailabilityID(Obj, ID);
			}
			cout << endl;
		}

	//Изменение объектов
	template<typename T>
	void ChangingObjectsPipe( unordered_map<int, Pipe>& MapP, Filter<T,Pipe> f, T param)
	{
		unordered_map<int, int> IDs;
		FilterResults(MapP, IDs, f, param);
		unordered_set<int> SetP;
		EnteringIDChange(IDs, SetP);
		
		SelectingAnEditAction(MapP, SetP, BatchEditingPipes);
	}	

	//Изменение объектов
void ChangingObjects(unordered_map<int, Pipe>& MapP, unordered_map<int, Cs>& MapCs)
{
	string Name = "NoName";
	unordered_set<int> SetObj;
	bool Status = false;
	int SizePipes = MapP.size();
	int SizeCs = MapCs.size();
	cout<< "1. Редактирование по фильтру названия труб" << endl
		<< "2. Редактирование по фильтру статуса трубы" << endl
		<< "3. Редактирование по ID труб" << endl
		<< "4. Редактирование по ID КС" << endl
		<< "0. Для возврата в главное меню." << endl << endl;

	int item = IntInput(0, 4);

	switch (item)
	{
	case 1:
		if (!CheckingPresenceElements(cout, SizePipes)) { return; }
		
		cout << endl;
		Name = EnteringFragmentName();
		
		ChangingObjectsPipe(MapP, CheckByName, Name);
		return;

	case 2:
		if (!CheckingPresenceElements(cout, SizePipes)) { return; }
		
		cout << endl;
		cout << "Введите 1, если статус искомых труб 'В работе' или 0, если их статус 'В ремонте'" << endl;
		Status = EnteringCheckingBool();

		ChangingObjectsPipe(MapP, CheckByStatus, Status);
		return;
	case 3:
		if (!CheckingPresenceElements(cout, SizePipes)) { return; }

		InputSetP(MapP, SetObj);
		SelectingAnEditAction(MapP, SetObj, Element_By_ElementEditingPipe);
		return;
	case 4:
		if (!CheckingPresenceElements(cout, SizeCs)) { return; }

		InputSetP(MapCs, SetObj);
		SelectingAnEditAction(MapCs, SetObj, Element_By_ElementEditingCs);
		return;
	case 0:
		return;
	}

	return;
}


//Вывод в файл
				//Перегрузка оператора вывода 
				ofstream& operator<<(ofstream& fout, const Pipe& p)
				{
					fout << p.GetName()<< endl<< p.GetLength() << endl<< p.GetDia() << endl << p.GetStatus()<<endl;
					return fout;
				}
				ofstream& operator<<(ofstream& fout, const Cs& Cs)
				{
					fout << Cs.GetName() << endl << Cs.GetWorkshop() << endl << Cs.GetWorkingWorkshops() << endl << Cs.GetEffectiveness() << endl;
					return fout;
				}
			//Вывод трубы и его ID в файл
			template<typename T>
			void OutputInFileObject(ofstream& fout, const unordered_map<int, T>& Obj)
		{
			for (auto itr = Obj.begin(); itr != Obj.end(); ++itr)
			{
				fout << itr->first << endl;
				fout << itr->second << endl;
			}
		}
		//Выбор способа сохранения
		void ChoosingSavingMethod(const unordered_map<int, Pipe>& MapP, const unordered_map<int, Cs>& MapCs, ofstream& fout)
		{
			int SizePipes = MapP.size();
			int SizeCs = MapCs.size();
			
			cout << "Введите 1 - для сохранения только труб." << endl
				<< "Введите 2 - для сохранения только КС." << endl
				<< "Введите 3 - для сохранения текущего состояния (КС и трубы)." << endl;
			int item = IntInput(1, 3);

			switch (item)
			{
			case 1:
				CheckingErrorsInFile(fout, CheckingPresenceElements, SizePipes);
				fout << SizePipes <<endl<<0<< endl;
				OutputInFileObject(fout, MapP);
				return;
			case 2:
				CheckingErrorsInFile(fout, CheckingPresenceElements, SizeCs);
				fout << 0 << endl << SizeCs << endl;
				OutputInFileObject(fout, MapCs);
				return;
			case 3:
				CheckingErrorsInFile(fout, CheckingPresenceElements, SizePipes);
				CheckingErrorsInFile(fout, CheckingPresenceElements, SizeCs);
				fout << MapP.size() << endl << SizeCs << endl;
				OutputInFileObject(fout, MapP);
				OutputInFileObject(fout, MapCs);
				return;
			}
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
//Вывод в файл 
void OutputInFile(const unordered_map<int,Pipe>& MapP, const unordered_map<int, Cs>& MapCs)
{
	cout << "5.Сохранение в файл." << endl;
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
		ChoosingSavingMethod(MapP, MapCs, fout);
		fout.close();
		cout << "Данные сохранены";
	}
	catch (const  ofstream::failure& ex)
	{
		cout << ex.what() << endl << ex.code() << endl << "Ошибка при открытии/создании файла" << endl;
	}
	
}

//Считывание из файла
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
			//Перегрузка ifstream на считывание Cs из файла с проверкой
			ifstream& operator>>(ifstream& fin, Cs& Cs)
			{
				fin >> ws;
				getline(fin, Cs._CsName);
				if (CheckingString(Cs._CsName) && СheckingIfstream(fin, Cs._CsWorkshop, 1) &&
					СheckingIfstream(fin, Cs._CsWorkingWorkshops, 0, Cs._CsWorkshop) &&
					СheckingIfstream(fin, Cs._CsEffectiveness, -100, 100))
				{
					return fin;
				}
				fin.setstate(std::ios_base::badbit);
				return fin;
			}
		//Считывание информации про объект из файла с проверкой
		template<typename T>
		bool ReadingInformationFile(ifstream& fin, unordered_map<int, T>& Obj)
		{
			int ObjID = 0;
			CheckingErrorsInFile(fin, CheckID, ObjID);
			T obj;
			fin >> obj;
			if ((Obj.find(ObjID) != Obj.end()) || fin.bad())
			{
				cout << "Для объекта c ID: " << ObjID << endl;
				cout << "Ошибка при чтении файла. В файле содержатся недопустимые значения" << endl;
				return false;
			}

			Obj.emplace(ObjID, obj);
			return true;
		}
	//Считывание объектов из файла
	template<typename T>
	void ReadingPipesFromFile(ifstream& fin, unordered_map<int, T>& Obj, int& Number)
		{
			unordered_map<int, T> Obj1;
			while (Number!= 0)
			{
				if (!ReadingInformationFile(fin, Obj1))
					return;
				--Number;
			}
			T::IDreplacement(Obj1);
			Obj.swap(Obj1);
		}
	void Skip(ifstream& fin, int NumberPipes)
	{
		int Skip;
		string StrSkip;
		Skip = NumberPipes * 5;
		while (Skip != 0)
		{
			fin >> ws;
			getline(fin, StrSkip);
			--Skip;
		}
	}
//Считывание из файла 
void ReadingFromFile(unordered_map<int, Pipe>& MapP, unordered_map<int, Cs>& MapCs)
{
	cout << "6.Загрузка данных из файла." << endl 
		 << "Данное действие приведёт к перезаписи введёных данных (если они есть). Убедитесь, что они вам не нужны." << endl
		 << "Введите 1, чтобы продолжить, либо 0 для отмены загрузки." << endl;
	if (EnteringCheckingBool())
	{
		ifstream fin;
		fin.exceptions(ifstream::failbit);
		int NumberPipes = 0;
		int NumberCs = 0;
		string way = EnteringFileName();

		try
		{
			fin.open(way, ios::in);
			CheckingErrorsInFile(fin, CheckingNumberElements, NumberPipes);
			CheckingErrorsInFile(fin, CheckingNumberElements, NumberCs);
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
				CheckingErrorsInFile(fin, CheckingPresenceElements, NumberCs);
				Skip(fin, NumberPipes);
				ReadingPipesFromFile(fin, MapCs, NumberCs);
				return;
			case 3:
				CheckingErrorsInFile(fin, CheckingPresenceElements, NumberPipes);
				CheckingErrorsInFile(fin, CheckingPresenceElements, NumberCs);
				ReadingPipesFromFile(fin, MapP, NumberPipes);
				ReadingPipesFromFile(fin, MapCs, NumberCs);
				return;
			}
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
int MainSharedConsole(unordered_map<int, Pipe>& MapP, unordered_map<int, Cs>& MapCs)
{
	int item = IntInput(0, 6);

	switch (item)
	{
		case 1:
			CreatingObject(MapP);
			PauseAndClearing();
			return true;
		case 2:
			CreatingObject(MapCs);
			PauseAndClearing();
			return true;
		case 3:
			InformationOutput(MapP,MapCs);
			return true;
		case 4:
			ChangingObjects(MapP, MapCs);
			PauseAndClearing();
			return true;
		case 5:
			OutputInFile(MapP, MapCs);
			PauseAndClearing();
			return true;
		case 6:
			ReadingFromFile(MapP, MapCs);
			PauseAndClearing();
			return true;
		case 0:
			cout << endl << "Вы хотите сохранить текущее состояние?" <<
				endl << "Введите 1 для сохранения или 0, для выхода из программы." << endl;
			if (EnteringCheckingBool()) { OutputInFile(MapP, MapCs);}
			return false;
	}
	
	return true;
}

//Точка входа в программу
int main() 
{
	setlocale(LC_ALL, "rus"); //Подключение руссофикатора
	unordered_map<int, Pipe> MapP;
	unordered_map<int, Cs> MapCs;
	//Запуск консоли
	do { cout << endl; TextSharedConsole();} while (MainSharedConsole(MapP,MapCs) != 0);
}