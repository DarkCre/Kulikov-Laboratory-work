#include <iostream> //подключаем библиотеку для работы с вводом и выводом (# - означает что это данные для ввода в препроцессор).
using namespace std; //указываем по умолчание стандартное пространство имён (std), для того, что бы не указывать перед элементами данного пространства откуда они.

struct Pipe //создание структуры труба
{
	double PipeLength; // Длина трубы
	double PipeDia;   //  Диаметр трубы
	bool PipeStatus; //   Статус трубы (в ремонте или нет)
}; 

struct Сs //создание структуры компрессорной станции
{
	string CsName; //имя КС
	int CsWorkshop; //количество цехов КС
	int CsWorkingWorkshops; //количество работающих цехов КС
	double Effectiveness; //эффективность КС
};

void TextSharedConsole() //текстовая часть консоли
{
	cout<< "1. Добавить трубу" << endl
		<< "2. Добавить КС" << endl
		<< "3. Просмотр всех объектов" << endl
		<< "4. Редактировать трубу" << endl
		<< "5. Редактировать КС" << endl
		<< "6. Сохранить" << endl
		<< "7. Загрузить" << endl
		<< "0. Выход" << endl;
}

void InputPipeLength(Pipe& p) //считывание длины трубы
{
	system("cls"); //https://www.cyberforum.ru/cpp-beginners/thread30713.html?ysclid=l8bdnuacc7726489405
	do
	{
		cout << "Введите длину трубы:"<<endl;
		cin >> p.PipeLength;
		if (cin.fail()) //проверка корректности данных
		{
			cin.clear();//сбрасываем биты ошибок
			cin.ignore(1000, '\n');//сбрасываем буфер с некорректными данными
			system("cls"); //чистим консоль
			cout << "Введено некоректное число, пожалуйста, повторите попытку." << endl;
		}
		else if (p.PipeLength <= 0.)
		{
			system("cls");
			cout << "Длина не может быть отрицательной или равной 0, пожалуйста, повторите попытку." << endl;
		}
	} while (cin.fail() || p.PipeLength <= 0.);
}

void InputPipeDia(Pipe& p) //считывание диаметра трубы
{
	system("cls");
	do
	{
		cout << "Введите диаметр трубы:" << endl;
		cin >> p.PipeDia;
		if (cin.fail())//проверка корректности данных
		{
			cin.clear();
			cin.ignore(1000, '\n');
			system("cls");
			cout << "Введено некоректное число, пожалуйста, повторите попытку." << endl;
		}
		else if (p.PipeDia <= 0.)
		{
			system("cls");
			cout << "Длина не может быть отрицательной или равной 0, пожалуйста, повторите попытку." << endl;
		}
	} while (cin.fail() || p.PipeDia <= 0.);
}

void InputPipeStatus(Pipe& p)//считывание статуса трубы
{
	system("cls");
	double check;
	do
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Введите статус трубы(в ремонте - 0, в работоспособном состоянии - 1): " << endl;
		cin >> check;
		if (cin.fail() || (check != 0 && check != 1)) //проверка корректности данных
		{
			system("cls");
			cout << "Указано некоректное число, пожалуйста, введите 0 или 1." << endl;
		}
		p.PipeStatus = check;
	} while (cin.fail() || (check != 0 && check != 1));

}

void InputPipe() //функциональная часть консоли
{
	Pipe p;
	InputPipeLength(p);
	InputPipeDia(p);
	InputPipeStatus(p);
} 

int MainSharedConsole() //скилет функциональной части консоли
{
	int item;
	cin >> item;
	switch (item)
	{
	case 1:
		InputPipe();
		break;
	case 2:
		cout << "2. Добавить КС";
		break;
	case 3:
		cout << "3. Просмотр всех объектов";
		break;
	case 4:
		cout << "4. Редактировать трубу";
		break;
	case 5:
		cout << "5. Редактировать КС";
		break;
	case 6:
		cout << "6. Сохранить";
		break;
	case 7:
		cout << "7. Загрузить";
		break;
	case 0:
		return 0;
		break;
	}
}

void SharedConsole() //главная консоль
{
	bool check = true;
	do
	{
		TextSharedConsole();
		check = MainSharedConsole();
	} while ((check!=0));
}

int main() //точка входа в программу
{
	setlocale(LC_ALL, "rus");
	SharedConsole();

	return 0;
}

