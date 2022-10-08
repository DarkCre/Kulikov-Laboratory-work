#include <iostream> //подключаем библиотеку для работы с вводом и выводом (# - означает что это данные для ввода в препроцессор).
#include <conio.h> // необходима для задержки, до нажатия клавиши
#include <fstream>// ввод в файл и вывод из файла
#include <string>
#include <unordered_map>
#include <typeinfo>

//указываем по умолчание стандартное пространство имён (std), для того, что бы не указывать перед элементами данного пространства откуда они.
using namespace std;

//Мои структуры
struct Pipe //создание структуры труба
{
	double PipeLength; // Длина трубы
	double PipeDia;   //  Диаметр трубы
	bool PipeStatus; //   Статус трубы (в ремонте или нет)
}; 

struct Cs //создание структуры компрессорной станции
{
	string CsName; //название КС
	int CsWorkshop; //количество цехов КС
	int CsWorkingWorkshops; //количество работающих цехов КС
	int CsEffectiveness; //эффективность КС
};

//Проверка ввода разных типов данных
	//Проверка на правильность ввода переменных типа int (в том числе с ограничениями) и положительный double
	template <typename T1>
	bool CheckingIntAndPositiveDouble(const T1& Variable,const T1& beginning = numeric_limits<T1>::min(), const T1& end = numeric_limits<T1>::max())
		// Вводим наше значение, а так же диапазон в котором оно должно находиться. Если мы введём значение без диапазона, то его диапазон будет равен
		// допустимому для данного типа данных диапазону. Т.о. в случае если ввидут число, которое нельзя ввести, то вылезет ошибка, однако если в
		// функцию подадут диапазон, то будет осуществлена проверка на то, входит ли значение в него.
		// https://stackoverflow.com/questions/1855459/maximum-value-of-int
		// http://studlab.com/news/parameiry_po_umolchaniju_i_peremennoe_chislo_parametrov_v_c/2013-06-22-766
	{
		string check = typeid(Variable).name();
		if (cin.fail() || cin.peek() != '\n' || Variable<beginning || Variable>end)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			if (check == "double") { cout << "Указаны некоректные данные. Пожалуйста, введите положительное число" << endl; }
			else { cout << "Указаны некоректные данные, пожалуйста, укажите целое число от " << beginning << " до " << end << endl << endl; }
			return false;
		}
		else if (check == "double" && Variable <= 0)
		{
			cout << "Это значение не может быть отрицательным или равным 0, пожалуйста, повторите попытку." << endl;
			return false;
		}
		return true;
	}
	//Ввод из файла и проверка Int и положительной double из файла
	template <typename T>
	bool ReadingFile_CheckingInt_Double(ifstream& fin, T& Variable)
	{
		fin >> Variable;
		if (fin.fail() || fin.peek() != '\n')
		{
			fin.clear();
			fin.ignore(1000, '\n');
			return true;
		}
	}
	//Проверка будевой строки на ошибки
	bool ErrorStringInBool(const string& String, bool& Bool, const string& Meaning)
	{
		if ((String.find_first_not_of("01") == string::npos) == true && String.length() == 1)
		{
			if (String[0] == '1') { Bool = 1; return false;}
			else if (String[0] == '0') { Bool = 0; return false;}
		}
		else
		{
			if (Meaning == "console") { cout<<"Указано некоректное число, пожалуйста, введите 0 или 1."<<endl; }
			else if (Meaning == "file") { return true; }
			return true;
		}
	}

//Подтверждение действий
bool СonfirmationSaving()
{
	double check = 0;
	cin >> check;
	if (check == 1.)
		return true;
	else
		return false;
}

//Ввод трубы
	//Ввод статуса трубы
	void InputPipeStatusCheck(bool& PipeStatus)
	{
		string strBool = "";
		do//Считывание статуса трубы
		{
			cout << "Введите статус трубы (в ремонте - 0, в работоспособном состоянии - 1): " << endl;
			cin >> strBool;
		} while (ErrorStringInBool(strBool, PipeStatus, "console") == true);
	}
	//Проверка правильности структуры Трубы (по смысловым критериям) ytn
	bool PipeInspection(const Pipe& p)
	{
		if ((CheckingIntAndPositiveDouble(p.PipeLength) == false) == true ||
			(CheckingIntAndPositiveDouble(p.PipeDia) == false) == true ||
			(p.PipeStatus == (true || false)))
		{
			return false;
		}
	}
//Ввод трубы
void InputPipe(unordered_map<int, Pipe>& MapP)
{
	Pipe p = {};

	cout << "1.Создание трубы:" << endl << endl;
	do//Считывание длины трубы
	{
		cout << "Введите длину трубы:" << endl;
		cin >> p.PipeLength;
	} while (CheckingIntAndPositiveDouble(p.PipeLength) == false);
	do//Считывание диаметра трубы
	{
		cout << "Введите диаметр трубы:" << endl;
		cin >> p.PipeDia;
	} while (CheckingIntAndPositiveDouble(p.PipeDia) == false);
	
	InputPipeStatusCheck(p.PipeStatus);

	MapP.emplace(MapP.size() + 1, p);
} 

//Ввод Кс ytn
//Ввод параметров Кс ytn
	void InputCsParameters(Cs& cs)
	{
		cout << "2.Создание компрессорной станции: " << endl << endl;
		//Считывание имени КС
		cout << "Введите название компрессорной станции (на латинском языке):" << endl;
		cin.ignore();
		getline(cin, cs.CsName);
		do//Считывание количества цехов КС
		{
			cout << "Введите количество цехов компрессорной станции:" << endl;
			cin >> cs.CsWorkshop;
			if (cs.CsWorkshop <= 0)
			{
				cout << "Цехов должно быть не меньше 1, пожалуйста, повторите попытку ввода." << endl;
			}
		} while (CheckingIntAndPositiveDouble(cs.CsWorkshop) == false || cs.CsWorkshop <= 0);
		do//Считывание количества рабочих цехов КС
		{
			cout << "Введите количество работающих цехов:" << endl;
			cin >> cs.CsWorkingWorkshops;
		} while (CheckingIntAndPositiveDouble(cs.CsWorkingWorkshops, 0, cs.CsWorkshop) == false);
		do//Считывание эффективности КС
		{
			cout << "Введите эффективность станции:" << endl;
			cin >> cs.CsEffectiveness;
		} while (CheckingIntAndPositiveDouble(cs.CsEffectiveness, -100, 100) == false);
	}
	//Проверка правильности структуры Кс (по смысловым критериям) ytn
	bool CsInspection(const Cs& cs)
	{
		if ((CheckingIntAndPositiveDouble(cs.CsWorkshop) == false || cs.CsWorkshop <= 0) == true ||
			(CheckingIntAndPositiveDouble(cs.CsWorkingWorkshops, 0, cs.CsWorkshop) == false) == true ||
			(CheckingIntAndPositiveDouble(cs.CsEffectiveness, -100, 100) == false) == true)
		{
			return false;
		}
	}
//Ввод Кс ytn
void InputCs(Cs& cs) //запрос на обновление всех данных по компрессорной станции и последовательность их ввода
{
	if (cs.CsWorkshop != 0)
	{
		cout << "Вы уверены, что хотите перезаписать данные по компрессорной станции?" << endl 
			 << "Введите 1 для подтверждения операции." << endl;
		if (СonfirmationSaving() == 1) { InputCsParameters(cs);}
	}
	else { InputCsParameters(cs);}
}

//Вывод информации по элементам ytn
void InformationOutput(const Pipe& p, const Cs& cs) //вывод информации по трубе и КС
{
	cout << "3.Информация по трубе:" << endl;
	if (p.PipeLength != 0)
		cout << endl << "Длина трубы: " <<p.PipeLength<< endl 
			 << "Диаметр трубы: " <<p.PipeDia<< endl 
			 << "Статус трубы: "<< (p.PipeStatus==true ? "В работе":"В ремонте") << endl;
	else { cout << "Данные не найдены. Сначала необходимо создать трубу." << endl;}

	cout << endl << "3.Информация по компрессорной станции:" << endl << endl;
	if (cs.CsWorkshop != 0)
	{
		cout << "Название: " << cs.CsName << endl 
			 << "Количество цехов: " << cs.CsWorkshop << endl 
			 << "Количество цехов в работе: " << cs.CsWorkingWorkshops << endl 
			 << "Эффективность: " << cs.CsEffectiveness<< endl;
		cout << endl << "Нажмите любую клавишу для продолжения."<< endl;
		_getch();//https://www.youtube.com/watch?v=6tGgasGBgmc - функция ожидания нажатия любой клавиши 
	}
	else
	{
		cout << "Данные не найдены. Сначала необходимо создать компрессорную станцию." << endl;
		cout << endl << "Нажмите любую клавишу для продолжения."<< endl;
		_getch();
	}
}

//Редактирование трубы ytn
void EditingPipe(bool& PipeStatus, const double& PipeLength) //редактирование трубы
{
	if (PipeLength != 0) 
	{
		cout << endl << "4.Редактирование трубы:" << endl << endl;
		InputPipeStatusCheck(PipeStatus);
		cout << endl << "Данные сохранены." << endl;
	}
	else 
	{ 
		cout << "Данные невозможно отредактировать. Сначала необходимо создать трубу." << endl;
		cout << endl << "Нажмите любую клавишу для продолжения." << endl;
		_getch();
	}
}

//Редактирование Кс (Текст и ввод) ytn
	//Редактирование Кс (функциональная часть) ytn
	bool FunctionalPartEditingCs(const int& CsWorkshop, int& CsWorkingWorkshops, const int& item) //функциональная часть изменения КС
	{
		int check1;
		int check2;
		check1 = CsWorkingWorkshops + 1;
		check2 = CsWorkingWorkshops - 1;

		switch (item)
		{
		case 1:
			if (check1 > CsWorkshop) { cout << "Невозможно запустить в работу больше цехов, чем существует. Пожалуйста, повторите попытку ввода." << endl; return false; }
			else
			{
				CsWorkingWorkshops++;
				cout << endl << "Данные сохранены." << endl;
				return true;
			}
		case 0:
			return true;
		case -1:
			if (check2 < 0) { cout << "Невозможно уменьшить количество работающих цехов, т.к. все цехи на данный момент остановлены." << endl; return false; }
			else
			{
				CsWorkingWorkshops--;
				cout << endl << "Данные сохранены." << endl;
				return true;
			}
		}
	}
//Редактирование Кс (Текст и ввод) ytn
void EditingCs(const int& CsWorkshop, int& CsWorkingWorkshops) //диалоговая часть редактирования КС
{	
	if (CsWorkshop != 0) 
	{
		int item;
		cout << endl << "5.Редактирование компрессорной станции:" << endl
			<< "На данный момент из "<< CsWorkshop<<" цехов в работе: " <<CsWorkingWorkshops << endl << endl;
		do
		{
			do
			{
				cout << "Введите 1 - для увеличения количества работающих цехов на 1." << endl
					<< "Введите 0 - для возврата в главное меню." << endl
					<< "Введите -1 - для уменьшения количества работающих цехов на 1." << endl;
				cin >> item;
			} while (CheckingIntAndPositiveDouble(item, -1, 1) == false);
		} while (FunctionalPartEditingCs(CsWorkshop, CsWorkingWorkshops, item) == false);
	}
	else
	{
		cout << "Данные невозможно отредактировать. Сначала необходимо создать компрессорную станцию." << endl;
		cout << endl << "Нажмите любую клавишу для продолжения" << endl;
		_getch();
	}
}

//Вывод в файл ytn
void OutputInFile(const Pipe& p, const Cs& cs)
{
	cout << "6.Сохранение в файл." << endl 
		 << "Данное действие приведёт к перезаписи файла data.txt."<<endl
		 << "Введите 1, чтобы продолжить, либо любое другое значение для отмены сохранения." << endl;
	if (СonfirmationSaving())
	{
		ofstream fout;
		fout.exceptions(ofstream::badbit | ofstream::failbit);
		//https://www.youtube.com/watch?v=jCW2wRoRi0U
		try
		{
			fout.open("data.txt", ios::out);

			fout << p.PipeLength << endl << p.PipeDia << endl << p.PipeStatus << endl;
			fout << cs.CsName << endl << cs.CsWorkshop << endl << cs.CsWorkingWorkshops << endl << cs.CsEffectiveness << endl;
			
			fout.close();
		}
		catch (const  ofstream::failure& ex)
		{
			cout << ex.what() << endl << ex.code() << endl << "Ошибка при открытии/создании файла" << endl;
		}
	}
}

//Считывание из файла ytn
	//Вывод ошибки считывания файла
	void OutputReadingError()
	{
		cout << "Ошибка при чтении файла. В файле содержатся недопустимые значения" << endl;
	}
	//Присвоение  значений из файла активными переменным
	void AssigningValuesFromFile(const Pipe& p1, const Cs& cs1, Pipe& p, Cs& cs)
	{
		if (CsInspection(cs1) == false || PipeInspection(p1) == false) { OutputReadingError();}
		else
		{
			cout << "Данные считаны." << endl;
			cs = cs1;
			p = p1;
		}
	}
//Считывание из файла ytn
void ReadingFromFile(Pipe& p, Cs& cs)
{
	cout << "7.Загрузка данных из файла." << endl 
		 << "Данное действие приведёт к перезаписи введёных данных (если они есть). Убедитесь, что они вам не нужны." << endl
		 << "Введите 1, чтобы продолжить, либо любое другое значение для отмены загрузки." << endl;
	if (СonfirmationSaving())
	{
		ifstream fin;
		fin.exceptions(ifstream::badbit | ifstream::failbit);
		string check;
		Pipe p1 = {};
		Cs cs1 = {};

		try
		{
			fin.open("data.txt", ios::in);
			//считывание данных
			if (ReadingFile_CheckingInt_Double(fin, p1.PipeLength) == true) { OutputReadingError(); return;}
			if (ReadingFile_CheckingInt_Double(fin, p1.PipeDia) == true) { OutputReadingError(); return;}
			fin >> check;
			if (ErrorStringInBool(check, p1.PipeStatus, "file") == true) { OutputReadingError(); return;};
			fin.ignore();
			getline(fin, cs1.CsName);
			if (ReadingFile_CheckingInt_Double(fin, cs1.CsWorkshop) == true) { OutputReadingError(); return;}
			if (ReadingFile_CheckingInt_Double(fin, cs1.CsWorkingWorkshops) == true) { OutputReadingError(); return;}
			if (ReadingFile_CheckingInt_Double(fin, cs1.CsEffectiveness) == true) { OutputReadingError(); return;}
			fin.close();

			AssigningValuesFromFile(p1, cs1, p, cs);
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
//Функциональная часть консоли
int MainSharedConsole(unordered_map<int, Pipe>& MapP,Pipe& p,Cs& cs) 
{
	cin.clear();

	int item =-1;
	do { cin >> item;} while (CheckingIntAndPositiveDouble(item, 0, 7) == false);

	switch (item)
	{
		case 1:
			system("cls");
			InputPipe(MapP);
			return true;
		case 2:
			system("cls");
			InputCs(cs);
			return true;
		case 3:
			system("cls");
			InformationOutput(p, cs);
			return true;
		case 4:
			system("cls");
			EditingPipe(p.PipeStatus, p.PipeLength);
			return true;
		case 5:
			system("cls");
			EditingCs(cs.CsWorkshop, cs.CsWorkingWorkshops);
			return true;
		case 6:
			system("cls");
			OutputInFile(p, cs);
			return true;
		case 7:
			system("cls");
			ReadingFromFile(p, cs);
			return true;
		case 0:
			if ((p.PipeLength != 0) || (cs.CsWorkshop != 0))
			{
				cout << endl << "Вы хотите сохранить текущее состояние?" <<
					endl << "Введите 1 для сохранения или любое другое значение, для выхода из программы." << endl;
				if (СonfirmationSaving() == true)
					OutputInFile(p, cs);
				else
					return false;
			}
			return false;
	}
	cin.ignore(1000, '\n');
}

//Точка входа в программу
int main() 
{
	setlocale(LC_ALL, "rus"); //Подключение руссофикатора
	unordered_map<int, Pipe> MapP;
	
	//Создание структур
	Pipe p = {};
	Cs cs = {};
	//Запуск консоли
	do { cout << endl; TextSharedConsole();} while (MainSharedConsole(MapP,p, cs) != 0);
}