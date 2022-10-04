#include <iostream> //подключаем библиотеку для работы с вводом и выводом (# - означает что это данные для ввода в препроцессор).
#include <conio.h> // необходима для задержки, до нажатия клавиши
#include <fstream>// ввод в файл и вывод из файла
#include <string>
using namespace std; //указываем по умолчание стандартное пространство имён (std), для того, что бы не указывать перед элементами данного пространства откуда они.

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
//Проверка на правильность ввода положительных переменных типа double
bool CheckingPositiveDouble(const double& Double) 
{
	if (cin.fail()|| cin.peek() != '\n') //проверка корректности данных
	{
		cin.clear();//сбрасываем биты ошибок
		cin.ignore(1000, '\n');//сбрасываем буфер с некорректными данными
		cout << "Введено некоректное число, пожалуйста, повторите попытку." << endl;
		return 0;
	}
	else if (Double <= 0.)
	{
		cout << "Это значение не может быть отрицательным или равным 0, пожалуйста, повторите попытку." << endl;
		return 0;
	}
	return 1;
}
//Проверка на правильность ввода переменных типа bool
bool CheckingBool(const bool& Bool) 
{
	if (cin.fail() || cin.peek() != '\n' || (Bool != 0 && Bool != 1)) //проверка корректности данных
	{
		cin.clear();//сбрасываем биты ошибок
		cin.ignore(1000, '\n');//сбрасываем буфер с некорректными данными
		cout << "Указано некоректное число, пожалуйста, введите 0 или 1." << endl;
		return 0;
	}
	return 1;
}
//Проверка на правильность ввода переменных типа int в указанном диапазоне
bool CheckingIntRange(const int& Int, const int& beginning,const int& end)
{
	if (cin.fail() || cin.peek() != '\n' || Int<beginning || Int>end)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Указано некоректное число, пожалуйста, укажите целое число от " << beginning << " до " << end << endl << endl;
		return 0;
	}
	return 1;
}
//Проверка на правильность ввода переменных типа int
bool CheckingInt(const int& Int)
{
	if (cin.fail() || cin.peek() != '\n')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Указаны некоректные данные, пожалуйста, укажите целое число"<< endl;
		return 0;
	}
	return 1;
}
//Проверка предпологаемой интовой строки на ошибки (с добавлением моих правок)
//https://www.techiedelight.com/ru/convert-string-to-int-cpp/   https://www.bestprog.net/ru/2018/04/26/working-with-strings-the-string-class-class-constructors-the-functions-assign-append-insert-replace-erase-find-rfind-compare-c_str-examples_ru/
bool ErrorStringInInt(const string& String, int& Int)
{
	if ((String.find_first_not_of("-0123456789") == string::npos) == 1)
	{
		try {
			Int = stoi(String);
			return 0;
		}
		catch (invalid_argument e) {
			return 1;
		}
	}
	else
	{
		return 1;
	}
}
//Проверка предпологаемой дабловой строки на ошибки (с добавлением моих правок)
bool ErrorStringInDouble(string& String, double& Double)
{
	if ((String.find_first_not_of("-.0123456789") == string::npos) == 1)
	{
		size_t found = String.find(".");
		size_t found2 = String.find(".", found + 1);
		if (String.length() > found)
			String.replace(found, 1, ",");
		if (String.length() > found2)
			return 1;
		else
		{
			try 
			{
			Double = stod(String); https://www.geeksforgeeks.org/stdstod-stdstof-stdstold-c/ // ммм запятую превращает в точку, а в случае с точкой отбрасывает дробную часть. Что не так с этим миром...
			return 0;
			}
			catch (invalid_argument e) 
			{
				return 1;
			}
		}
	}
	else
		return 1;
}
//Проверка предпологаемой будевой строки на ошибки (с добавлением моих правок)
bool ErrorStringInBool(const string& String, bool& Bool)
{
	if ((String.find_first_not_of("01") == string::npos) == 1 && String.length() == 1)
	{
		if (String[0] == '1')
		{
			Bool = 1;
			return 0;
		}
		else if (String[0] == '0')
		{
			Bool = 0;
			return 0;
		}
	}
	else
	{
		return 1;
	}
}
//Подтверждение действий
bool СonfirmationSaving()
{
	double check = 0;
	cin >> check;
	if (check == 1.)
		return 1;
	else
		return 0;
}

//Текст главной консоли
void TextSharedConsole() //текстовая часть консоли
{
	cout<<" Главное меню: "<<endl
		<<"1. Добавить трубу" << endl
		<< "2. Добавить КС" << endl
		<< "3. Просмотр всех объектов" << endl
		<< "4. Редактировать трубу" << endl
		<< "5. Редактировать КС" << endl
		<< "6. Сохранить" << endl
		<< "7. Загрузить" << endl
		<< "0. Выход" << endl << endl;
}

//Ввод параметров трубы
void InputPipeParameters(Pipe& p)
{
	cout << "1.Создание трубы:" << endl << endl;
	do//Считывание длины трубы
	{
		cout << "Введите длину трубы:"<<endl;
		cin >> p.PipeLength;
	} while (CheckingPositiveDouble(p.PipeLength)==false);
	do//Считывание диаметра трубы
	{
		cout << "Введите диаметр трубы:" << endl;
		cin >> p.PipeDia;
	} while (CheckingPositiveDouble(p.PipeDia) == false);
	do//Считывание статуса трубы
	{
		cout << "Введите статус трубы (в ремонте - 0, в работоспособном состоянии - 1): " << endl;
		cin >> p.PipeStatus;
	} while (CheckingBool(p.PipeStatus) == false);
}

//Ввод трубы
void InputPipe(Pipe& p) //запрос на обновление всех данных по трубе и последовательность их ввода 
{
	if (p.PipeLength != 0)
	{
		cout << "Вы уверены, что хотите перезаписать данные по трубе?" << endl
			 << "Введите 1 для подтверждения операции" << endl;
		if (СonfirmationSaving() == 1){ InputPipeParameters(p);}
	}
	else {InputPipeParameters(p);}
} 

//Проверка правильности структуры Трубы (по смысловым критериям)
bool PipeInspection(const Pipe& p)
{
	if ((CheckingPositiveDouble(p.PipeLength) == false) == 1 ||
		(CheckingPositiveDouble(p.PipeDia) == false) == 1 ||
		(CheckingBool(p.PipeStatus) == false) == 1) 
	{ return 0;}
}

//Ввод параметров Кс
void InputCsParameters(Cs& cs)
{
	cout << "2.Создание компрессорной станции: " << endl << endl;
	//Считывание имени КС
	cout << "Введите название компрессорной станции (на латинском языке):" << endl;
		cin.ignore();
		getline(cin,cs.CsName);
	do//Считывание количества цехов КС
	{
		cout << "Введите количество цехов компрессорной станции:" << endl;
		cin >> cs.CsWorkshop;
		if (cs.CsWorkshop <= 0)
		{
			cout << "Цехов должно быть не меньше 1, пожалуйста, повторите попытку ввода." << endl;
		}
	} while (CheckingInt(cs.CsWorkshop) == false || cs.CsWorkshop <= 0);
	do//Считывание количества рабочих цехов КС
	{
		cout << "Введите количество работающих цехов:" << endl;
		cin >> cs.CsWorkingWorkshops;
	} while (CheckingIntRange(cs.CsWorkingWorkshops, 0, cs.CsWorkshop) == false);
	do//Считывание эффективности КС
	{
		cout << "Введите эффективность станции:" << endl;
		cin >> cs.CsEffectiveness;
	} while (CheckingIntRange(cs.CsEffectiveness, -100, 100) == false);
}

//Ввод Кс
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

//Проверка правильности структуры Кс (по смысловым критериям)
bool CsInspection(const Cs& cs)
{
	if ((CheckingInt(cs.CsWorkshop) == false || cs.CsWorkshop <= 0) == 1 ||
		(CheckingIntRange(cs.CsWorkingWorkshops, 0, cs.CsWorkshop) == false) == 1 ||
		(CheckingIntRange(cs.CsEffectiveness, -100, 100) == false) == 1)
	{ return 0;}
}

//Вывод информации по элементам
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

//Редактирование трубы
void EditingPipe(bool& PipeStatus, const double& PipeLength) //редактирование трубы
{
	if (PipeLength != 0) 
	{
		cout << endl << "4.Редактирование трубы:" << endl << endl;
		do
		{
			cout << "Введите обновлённый статус трубы (в ремонте - 0, в работоспособном состоянии - 1): " << endl;
			cin >> PipeStatus;
		} while (CheckingBool(PipeStatus) == false);
		cout << endl << "Данные сохранены." << endl;
	}
	else 
	{ 
		cout << "Данные невозможно отредактировать. Сначала необходимо создать трубу." << endl;
		cout << endl << "Нажмите любую клавишу для продолжения." << endl;
		_getch();
	}
}

//Редактирование Кс (функциональная часть)
bool FunctionalPartEditingCs(const int& CsWorkshop, int& CsWorkingWorkshops, const int& item) //функциональная часть изменения КС
{
	int check1;
	int check2;
	check1 = CsWorkingWorkshops + 1;
	check2 = CsWorkingWorkshops - 1;

	switch (item)
	{
	case 1:
		if (check1 > CsWorkshop) { cout << "Невозможно запустить в работу больше цехов, чем существует. Пожалуйста, повторите попытку ввода." << endl; return 0; }
		else
		{
			CsWorkingWorkshops++;
			cout << endl << "Данные сохранены." << endl;
			return 1;
		}
	case 0:
		return 1;
	case -1:
		if (check2 < 0) { cout << "Невозможно уменьшить количество работающих цехов, т.к. все цехи на данный момент остановлены." << endl; return 0; }
		else
		{
			CsWorkingWorkshops--;
			cout << endl << "Данные сохранены." << endl;
			return 1;
		}
	}
}
//Редактирование Кс (Текст и ввод)
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
			} while (CheckingIntRange(item, -1, 1) == false);
		} while (FunctionalPartEditingCs(CsWorkshop, CsWorkingWorkshops, item) == false);
	}
	else
	{
		cout << "Данные невозможно отредактировать. Сначала необходимо создать компрессорную станцию." << endl;
		cout << endl << "Нажмите любую клавишу для продолжения" << endl;
		_getch();
	}
}

//Вывод в файл
void OutputInFile(const Pipe& p, const Cs& cs)
{
	cout << "6.Сохранение в файл." << endl 
		 << "Данное действие приведёт к перезаписи файла data.txt."<<endl
		 << "Введите 1, чтобы продолжить, либо любое другое значение для отмены сохранения." << endl;
	if (СonfirmationSaving())
	{
		ofstream fout;
		fout.open("data.txt", ios::out);
		if (fout.is_open())
		{
			fout << p.PipeLength << endl << p.PipeDia << endl << p.PipeStatus << endl;
			fout << cs.CsName << endl << cs.CsWorkshop << endl << cs.CsWorkingWorkshops << endl << cs.CsEffectiveness << endl;
			fout.close();
			cout << "Данные сохранены." << endl;
		}
		else { cout << "Не удалось открыть файл.";}
	}
}

//Присвоение  значений из файла активными переменным
void AssigningValuesFromFile(const Pipe& p1, const Cs& cs1, Pipe& p, Cs& cs)
{
	if (CsInspection(cs1) == 0 || PipeInspection(p1) == 0) { OutputReadingError();}
	else
	{
		cout << "Данные считаны." << endl;
		cs = cs1;
		p = p1;
	}
}

//Вывод ошибки считывания файла
void OutputReadingError()
{
	cout << "Ошибка при чтении файла. В файле содержатся недопустимые значения" << endl;
}
//Считывание из файла
void ReadingFromFile(Pipe& p, Cs& cs)
{
	cout << "7.Загрузка данных из файла." << endl 
		 << "Данное действие приведёт к перезаписи введёных данных (если они есть). Убедитесь, что они вам не нужны." << endl
		 << "Введите 1, чтобы продолжить, либо любое другое значение для отмены загрузки." << endl;
	if (СonfirmationSaving())
	{
		ifstream fin;
		string check;
		Pipe p1 = {};
		Cs cs1 = {};

		fin.open("data.txt", ios::in);
		if (fin.is_open())
		{
			fin >> check;
			if (ErrorStringInDouble(check, p1.PipeLength) == 1) { OutputReadingError(); return; }
			fin >> check;
			if (ErrorStringInDouble(check, p1.PipeDia) == 1) { OutputReadingError(); return; }
			fin >> check;
			if (ErrorStringInBool(check, p1.PipeStatus) == 1) { OutputReadingError(); return; }
			fin.ignore();
			getline(fin, cs1.CsName);
			fin >> check;
			if (ErrorStringInInt(check, cs1.CsWorkshop) == 1) { OutputReadingError(); return; }
			fin >> check;
			if (ErrorStringInInt(check, cs1.CsWorkingWorkshops) == 1) { OutputReadingError(); return; }
			fin >> check;
			if (ErrorStringInInt(check, cs1.CsEffectiveness) == 1) { OutputReadingError(); return; }
			fin.close();
			AssigningValuesFromFile(p1, cs1, p, cs);
		}
		else { cout << "Не удалось открыть файл.";}
	}
}

//Главная консоль
int MainSharedConsole(Pipe& p,Cs& cs) //скелет функциональной части консоли
{
	int item;
	do { cin >> item;} while (CheckingIntRange(item, 0, 7) == false);

	switch (item)
	{
		case 1:
			system("cls");
			InputPipe(p);
			return 1;
		case 2:
			system("cls");
			InputCs(cs);
			return 1;
		case 3:
			system("cls");
			InformationOutput(p, cs);
			return 1;
		case 4:
			system("cls");
			EditingPipe(p.PipeStatus, p.PipeLength);
			return 1;
		case 5:
			system("cls");
			EditingCs(cs.CsWorkshop, cs.CsWorkingWorkshops);
			return 1;
		case 6:
			system("cls");
			OutputInFile(p, cs);
			return 1;
		case 7:
			system("cls");
			ReadingFromFile(p, cs);
			return 1;
		case 0:
			if ((p.PipeLength != 0) || (cs.CsWorkshop != 0))
			{
				cout << endl << "Вы хотите сохранить текущее состояние?" <<
					endl << "Введите 1 для сохранения или любое другое значение, для выхода из программы." << endl;
				if (СonfirmationSaving() == 1)
					OutputInFile(p, cs);
				else
					return 0;
			}
			return 0;
	}
}

//Точка входа в программу
int main() 
{
	setlocale(LC_ALL, "rus"); //Подключение руссофикатора
	//Создание структур
	Pipe p = {};
	Cs cs = {};
	//Запуск консоли
	do { cout << endl; TextSharedConsole();} while (MainSharedConsole(p, cs) != 0);
}