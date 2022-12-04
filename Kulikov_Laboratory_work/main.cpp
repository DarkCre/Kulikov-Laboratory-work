#include <conio.h> // необходима для задержки, до нажатия клавиши
#include "Pipe.h"
#include "Checking.h"
#include "Cs.h"
#include "OutputAndMmodification.h"
#include "OperatorOverloads.h"
#include "WorkingWithFiles.h"

//Указываем по умолчание стандартное пространство имён (std), для того, что бы не указывать перед элементами данного пространства откуда они.
using namespace std;
//Пауза
void PauseAndClearing()
{
	cout << endl << "Нажмите любую клавишу для возврата в главное меню." << endl;
	_getch();
	system("cls");
}


//Создание нового элемента
template<typename T>
void CreatingObject(unordered_map<int, T>& Obj)
{
	T obj;
	cin>>obj;
	Obj.emplace(obj.GetID(), obj);
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
	do { 
		cout << endl;
		cout << " Главное меню: " << endl
			<< "1. Добавить трубу" << endl
			<< "2. Добавить КС" << endl
			<< "3. Просмотр всех объектов" << endl
			<< "4. Изменение объектов" << endl
			<< "5. Сохранить" << endl
			<< "6. Загрузить" << endl
			<< "0. Выход" << endl << endl;
	} while (MainSharedConsole(MapP,MapCs) != 0);
}