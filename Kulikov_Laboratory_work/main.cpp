#include <iostream> //подключаем библиотеку для работы с вводом и выводом (# - означает что это данные для ввода в препроцессор).
#include <conio.h> // необходима для задержки, до нажатия клавиши
#include <fstream>// ввод в файл и вывод из файла
using namespace std; //указываем по умолчание стандартное пространство имён (std), для того, что бы не указывать перед элементами данного пространства откуда они.

//мои структуры
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
bool CheckingPositiveDouble(const double& Double) //проверка на правильность ввода положительных переменных типа double
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

bool CheckingBool(const bool& Bool) //проверка на правильность ввода переменных типа bool
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

bool CheckingIntRange(const int& Int, const int& beginning,const int& end) //проверка на правильность ввода переменных типа int в указанном диапазоне
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

bool CheckingInt(const int& Int) //проверка на правильность ввода переменных типа int
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


//Текст главной консоли
void TextSharedConsole() //текстовая часть консоли
{
	cout<<"Главное меню"<<endl
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
void InputPipeLength(Pipe& p) //считывание длины трубы
{
	do
	{
		cout << "Введите длину трубы:"<<endl;
		cin >> p.PipeLength;
	} while (CheckingPositiveDouble(p.PipeLength)==false);
}

void InputPipeDia(Pipe& p) //считывание диаметра трубы
{
	do
	{
		cout << "Введите диаметр трубы:" << endl;
		cin >> p.PipeDia;
		
	} while (CheckingPositiveDouble(p.PipeDia)==false);
}

void InputPipeStatus(Pipe& p)//считывание статуса трубы
{
	do
	{
		cout << "Введите статус трубы(в ремонте - 0, в работоспособном состоянии - 1): " << endl;
		cin >> p.PipeStatus;
	} while (CheckingBool(p.PipeStatus)==false);
}

//Ввод трубы
void InputPipe(Pipe& p) //запрос на обновление всех данных по трубе и последовательность их ввода 
{
	double check=0;
	if (p.PipeLength != 0)
	{
		cout << "Вы уверены что хотите перезаписать данные по трубе?" << endl << "Введите 1 для подтверждения операции" << endl;
		cin >> check;
		if (check == 1)
		{
			cout << "Создание трубы:" << endl << endl;
			InputPipeLength(p);
			InputPipeDia(p);
			InputPipeStatus(p);
		}
		else
		{
			cin.clear();
			cin.ignore(1000, '\n');
			return;
		}
	}
	else
	{
		cout << "Создание трубы:" << endl << endl;
		InputPipeLength(p);
		InputPipeDia(p);
		InputPipeStatus(p);
	}

} 

//Ввод параметров Кс
void InputCsName(Cs& cs) //считывание имени КС
{
	cout << "Введите название компрессорной станции" << endl;
	cin >> cs.CsName;
}

void InputCsWorkshop(Cs& cs) //считывание количества цехов КС
{
	do
	{
		cout << "Введите количество цехов компрессорной станции" << endl;
		cin >> cs.CsWorkshop;
		if (cs.CsWorkshop <= 0)
		{
			cout << "Цехов должно быть не меньше 1, пожалуйста, повторите попытку ввода." << endl;
		}
	} while (CheckingInt(cs.CsWorkshop) == false || cs.CsWorkshop <= 0);
}

void InputCsWorkingWorkshops(Cs& cs) //считывание количества рабочих цехов КС
{
	do
	{
		cout << "Введите количество работающих цехов" << endl;
		cin >> cs.CsWorkingWorkshops;
	} while (CheckingIntRange(cs.CsWorkingWorkshops,0,cs.CsWorkshop) == false);
}

void InputCsEffectiveness(Cs& cs) //считывание эффективности КС
{
	do
	{
		cout << "Введите эффективность станции:" << endl;
		cin >> cs.CsEffectiveness;
	} while (CheckingIntRange(cs.CsEffectiveness,-100,100) == false);
}

//Ввод Кс
void InputCs(Cs& cs) //запрос на обновление всех данных по компрессорной станции и последовательность их ввода
{
	double check=0;
	if (cs.CsWorkshop != 0)
	{
		cout << "Вы уверены что хотите перезаписать данные по компрессорной станции?" << endl << "Введите 1 для подтверждения операции" << endl;
		cin >> check;
		if (check == 1)
		{
			cout << "Создание компрессорной станции: " << endl << endl;
			InputCsName(cs);
			InputCsWorkshop(cs);
			InputCsWorkingWorkshops(cs);
			InputCsEffectiveness(cs);
		}
		else
		{
			cin.clear();
			cin.ignore(1000, '\n');
			return;
		}
	}
	else
	{
		cout << "Создание компрессорной станции:" << endl << endl;
		InputCsName(cs);
		InputCsWorkshop(cs);
		InputCsWorkingWorkshops(cs);
		InputCsEffectiveness(cs);
	}

}

//Информация по элементам
void InformationOutput(const Pipe& p, const Cs& cs) //вывод информации по трубе и КС
{
	cout << "Информация по трубе:" << endl;
	if (p.PipeLength != 0)
		cout << endl << "Длина трубы: " <<p.PipeLength<< endl << "Диаметр трубы: " <<p.PipeDia<< endl << "Статус трубы: "<< (p.PipeStatus==true ? "В работе":"В ремонте") << endl;
	else
	{
		cout << "Данные не найдены. Сначала необходимо создать трубу." << endl;
	}

	cout << endl << "Информация по компрессорной станции:" << endl;
	if (cs.CsWorkshop != 0)
	{
		cout << endl << "Название: " << cs.CsName << endl << "Количество цехов: " << cs.CsWorkshop << endl << "Количество цехов в работе: " << cs.CsWorkingWorkshops << endl << "Эффективность: " << cs.CsEffectiveness<< endl;
		_getch();//https://www.youtube.com/watch?v=6tGgasGBgmc - функция ожидания нажатия любой клавиши 
	}
	else
	{
		cout << "Данные не найдены. Сначала необходимо создать компрессорную станцию." << endl;
		_getch();
	}
}

//Редактирование трубы
void EditingPipe(bool& PipeStatus) //редактирование трубы
{
	cout << endl << "Редактирование трубы:" << endl;
	do
	{
		cout << "Введите обновлённый статус трубы(в ремонте - 0, в работоспособном состоянии - 1): " << endl;
		cin >> PipeStatus;
	} while (CheckingBool(PipeStatus) == false);
	cout << endl << "Данные сохранены." << endl;
}

//Редактирование Кс (функциональная часть)
bool FunctionalPartEditingCs(Cs& cs, const int& item) //функциональная часть изменения КС
{
	int check1;
	int check2;
	check1 = cs.CsWorkingWorkshops + 1;
	check2 = cs.CsWorkingWorkshops - 1;
	if (check1 > cs.CsWorkshop && item==1)
	{
		cout << "Невозможно запустить в работу больше цехов, чем существует. Пожалуйста, повторите попытку ввода." << endl;
		return 0;
	}
	else if (item == 1)
	{
		cs.CsWorkingWorkshops++;
		cout << endl << "Данные сохранены." << endl;
		return 1;
	}
	else if (item == 0)
	{
		return 1;
	}
	else if (check2 < 0 && item == -1)
	{
		cout << "Невозможно уменьшить количество работающих цехов, т.к. все цехи на данный момент остановлены." << endl;
		return 0;
	}
	else if (item == -1)
	{
		cs.CsWorkingWorkshops--;
		cout << endl << "Данные сохранены." << endl;
		return 1;
	}
}
//Редактирование Кс (Текст и ввод)
void EditingCs(Cs& cs) //диалоговая часть редактирования КС
{	
int item;
	cout << endl << "Редактирование компрессорной станции:" << endl
				 <<"На данный момент цехов в работе: "<< cs.CsWorkingWorkshops << endl << endl;
	do
	{
		do
		{
			cout << "Введите 1 - для увеличения количества работающих цехов на 1." << endl
				<< "Введите 0 - для возврата в главное меню." << endl
				<< "Введите -1 - для уменьшения количества работающих цехов на 1." << endl;
			cin >> item;
		} while (CheckingIntRange(item, -1, 1) == false);
	
	} while (FunctionalPartEditingCs(cs,item) == false);
}

//Вывод в файл
void OutputInFile(const Pipe& p, const Cs& cs)
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
	else
	{
		cout << "Не удалось открыть файл.";
	}
}

//Считывание из файла
void ReadingFromFile(Pipe& p, Cs& cs)
{
	ifstream fin;
	fin.open("data.txt", ios::in);
	if (fin.is_open())
	{
		fin >> p.PipeLength;
		fin >> p.PipeDia;
		fin >> p.PipeStatus;
		fin >> cs.CsName;
		fin >> cs.CsWorkshop;
		fin >> cs.CsWorkingWorkshops;
		fin >> cs.CsEffectiveness;
		fin.close();
		cout << "Данные считаны." << endl;
	}
	else
	{
		cout << "Не удалось открыть файл.";
	}
}

//Главная консоль
int MainSharedConsole(Pipe& p, Cs& cs) //скилет функциональной части консоли
{
	int item;
	do
	{
		cin >> item;
	} while (CheckingIntRange(item, 0, 7) == false);
	
	switch (item)
	{
	case 1:
		InputPipe(p);
		break;
	case 2:
		InputCs(cs);
		break;
	case 3:
		InformationOutput(p, cs);
		break;
	case 4:
		if (p.PipeLength != 0)
		{
			EditingPipe(p.PipeStatus);
		}
		else
		{
			cout << "Данные не возможно отредактировать. Сначала необходимо создать трубу." << endl;
			_getch();
		}
		break;
	case 5:
		if (cs.CsWorkshop != 0)
		{
			EditingCs(cs);
		}
		else
		{
			cout << "Данные не возможно отредактировать. Сначала необходимо создать компрессорную станцию." << endl;
			_getch();
		}
		break;
	case 6:
		OutputInFile(p, cs);
		break;
	case 7:
		ReadingFromFile(p, cs);
		break;
	case 0:
		return 0;
		break;
	}
}

void SharedConsole() //главная консоль
{
	Pipe p = {};
	Cs cs = {};
	bool check = true;
	do
	{
		cout << endl;
		TextSharedConsole();
		check = MainSharedConsole(p,cs);
	} while ((check!=0));
}



int main() //точка входа в программу
{
	setlocale(LC_ALL, "rus");
	SharedConsole();

	return 0;
}

