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


void InputPipe(Pipe& p) //последовательность ввода данных по трубе
{
	double check;
	if (p.PipeLength != 0)
	{
		cout << "Вы уверены что хотите перезаписать данные по трубе?" << endl << "Введите 1 для подтверждения операции" << endl;
		cin >> check;
		if (check == true)
		{
			cout << "Создание трубы" << endl;
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
		cout << "Создание трубы" << endl;
		InputPipeLength(p);
		InputPipeDia(p);
		InputPipeStatus(p);
	}

} 


int MainSharedConsole(Pipe& p) //скилет функциональной части консоли
{
	int item;
	cin >> item;
	switch (item)
	{
	case 1:
		InputPipe(p);
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
	Pipe p = {};
	bool check = true;
	do
	{
		TextSharedConsole();
		check = MainSharedConsole(p);
	} while ((check!=0));
}


int main() //точка входа в программу
{
	setlocale(LC_ALL, "rus");
	SharedConsole();

	return 0;
}

