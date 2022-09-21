#include <iostream> //подключаем библиотеку для работы с вводом и выводом (# - означает что это данные для ввода в препроцессор).
using namespace std; //указываем по умолчание стандартное пространство имён (std), для того, что бы не указывать перед элементами данного пространства откуда они.

void TextSharedConsole()
{
	cout << "1. Добавить трубу" << endl
		<< "2. Добавить КС" << endl
		<< "3. Просмотр всех объектов" << endl
		<< "4. Редактировать трубу" << endl
		<< "5. Редактировать КС" << endl
		<< "6. Сохранить" << endl
		<< "7. Загрузить" << endl
		<< "0. Выход" << endl;
}

int MainSharedConsole()
{
	int item;
	cin >> item;
	switch (item)
	{
	case 1:
		cout << "1. Добавить трубу";
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
		cout << "0. Выход";
		return 0;
		break;
	default:
		break;
	}
}


void SharedConsole()
{
	bool check = true;
	do
	{
		TextSharedConsole();
		check = MainSharedConsole();
	} while ((check!=0));
}

int main() //функция, которая всегда выполняется первой (точка входа в программу)
{
	setlocale(LC_ALL, "rus");
	SharedConsole();

	return 0;
}

