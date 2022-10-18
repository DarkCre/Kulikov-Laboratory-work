#include <iostream> //подключаем библиотеку для работы с вводом и выводом (# - означает что это данные для ввода в препроцессор).
#include <conio.h> // необходима для задержки, до нажатия клавиши
#include <fstream>// ввод в файл и вывод из файла
#include <string>
#include <unordered_map>

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
	//Проверка на правильность ввода переменных c диапазоном для консоли и файла
	template <typename T>
	bool СheckingValues(const T& Variable, istream& in = cin,const T& beginning = numeric_limits<T>::min(), const T& end = numeric_limits<T>::max())
		// Вводим наше значение, а так же диапазон в котором оно должно находиться. Если мы введём значение без диапазона, то его диапазон будет равен
		// допустимому для данного типа данных диапазону. Т.о. в случае если ввидут число, которое нельзя ввести, то вылезет ошибка, однако если в
		// функцию подадут диапазон, то будет осуществлена проверка на то, входит ли значение в него.
		// https://stackoverflow.com/questions/1855459/maximum-value-of-int
		// http://studlab.com/news/parameiry_po_umolchaniju_i_peremennoe_chislo_parametrov_v_c/2013-06-22-766
	{
		if (in.fail() || in.peek() != '\n' || Variable<beginning || Variable>end)
		{
			in.clear();
			in.ignore(1000, '\n');
			cout << "Указаны некоректные данные, пожалуйста, укажите число от " << beginning << " до " << end << endl << endl;
			return false;
		}
		return true;
	}

	template <typename T>
	bool СheckingIfstream(ifstream& fin, T& Variable, const T& beginning = numeric_limits<T>::min(), const T& end = numeric_limits<T>::max())
	{
		fin >> Variable;
		return СheckingValues(Variable, fin, beginning, end);
	}

	//Ввод с проверкой будевой строки на ошибки
	bool EnteringCheckingBool()
	{
		char ch;
		do
		{
			cin >> ch;
		} while (!СheckingValues(ch, cin, '0', '1'));
		if (ch == '1')
		{
			return true;
		}
		return false;
	}


	//Ввод статуса трубы
	void InputPipeStatusCheck(bool& PipeStatus)
	{
		//Считывание статуса трубы
		cout << "Введите статус трубы (в ремонте - 0, в работоспособном состоянии - 1): " << endl;
		EnteringCheckingBool();
	}
//Ввод трубы
void InputPipe(unordered_map<int, Pipe>& MapP)
{
	Pipe p = {};

	cout << "1.Создание трубы:" << endl << endl;
	do//Считывание длины трубы
	{
		cout << "Введите длину трубы (0.00):" << endl;
		cin >> p.PipeLength;
	} while (!СheckingValues(p.PipeLength,cin,0.));
	do//Считывание диаметра трубы
	{
		cout << "Введите диаметр трубы (0.00):" << endl;
		cin >> p.PipeDia;
	} while (!СheckingValues(p.PipeDia,cin, 0.));
	
	InputPipeStatusCheck(p.PipeStatus);

	MapP.emplace(MapP.size() + 1, p);
} 
	
	//Ввод параметров Кс ytn
	void InputCsParameters(Cs& cs)
	{
		cout << "2.Создание компрессорной станции: " << endl << endl;
		//Считывание имени КС
		cout << "Введите название компрессорной станции (на латинском языке):" << endl;
		cin>>ws;
		getline(cin, cs.CsName);
		do//Считывание количества цехов КС
		{
			cout << "Введите количество цехов компрессорной станции (Целое, положительное число):" << endl;
			cin >> cs.CsWorkshop;
			if (cs.CsWorkshop <= 0)
			{
				cout << "Цехов должно быть не меньше 1!" << endl;
			}
		} while (!СheckingValues(cs.CsWorkshop, cin, 0));
		do//Считывание количества рабочих цехов КС
		{
			cout << "Введите количество работающих цехов (Целое, положительное число, которое меньше количества цехов):" << endl;
			cin >> cs.CsWorkingWorkshops;
		} while (!СheckingValues(cs.CsWorkingWorkshops, cin, 0, cs.CsWorkshop));
		do//Считывание эффективности КС
		{
			cout << "Введите эффективность станции (Целое число от -100 до 100):" << endl;
			cin >> cs.CsEffectiveness;
		} while (СheckingValues(cs.CsEffectiveness, cin, -100, 100) == false);
	}

//Ввод Кс ytn
void InputCs(Cs& cs) //запрос на обновление всех данных по компрессорной станции и последовательность их ввода
{
	if (cs.CsWorkshop != 0)
	{
		cout << "Вы уверены, что хотите перезаписать данные по компрессорной станции?" << endl
			<< "Введите 1 для подтверждения операции." << endl;
		if (!EnteringCheckingBool())
			return;
	}
	InputCsParameters(cs);
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
	}
	else
	{
		cout << "Данные не найдены. Сначала необходимо создать компрессорную станцию." << endl;
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
	}
}

//Редактирование Кс ytn
void EditingCs(const int& CsWorkshop, int& CsWorkingWorkshops) //диалоговая часть редактирования КС
{	
	if (CsWorkshop == 0)
	{
		cout << "Данные невозможно отредактировать. Сначала необходимо создать компрессорную станцию." << endl;
		return;
	}

	int item;
	cout << endl << "5.Редактирование компрессорной станции:" << endl
		<< "На данный момент из "<< CsWorkshop<<" цехов в работе: " <<CsWorkingWorkshops << endl << endl;

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
		if (CsWorkingWorkshops == CsWorkshop)
		{
			cout << "Невозможно запустить в работу больше цехов, чем существует. Пожалуйста, повторите попытку ввода." << endl;
			return;
		}
		else
		{
			++CsWorkingWorkshops;
			break;
		}
	case 0:
		return;
	case -1:
		if (CsWorkingWorkshops == 0)
		{
			cout << "Невозможно уменьшить количество работающих цехов, т.к. все цехи на данный момент остановлены." << endl;
			return;
		}
		else
		{
			--CsWorkingWorkshops;
			break;
		}
	}
	cout << endl << "Данные сохранены." << endl;
}

//Вывод в файл ytn
void OutputInFile(const Pipe& p, const Cs& cs)
{
	cout << "6.Сохранение в файл." << endl 
		 << "Данное действие приведёт к перезаписи файла data.txt."<<endl
		 << "Введите 1, чтобы продолжить, либо 0 для отмены." << endl;
	if (EnteringCheckingBool())
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
			cout << "Данные сохранены";
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

//Считывание из файла ytn
void ReadingFromFile(Pipe& p, Cs& cs)
{
	cout << "7.Загрузка данных из файла." << endl 
		 << "Данное действие приведёт к перезаписи введёных данных (если они есть). Убедитесь, что они вам не нужны." << endl
		 << "Введите 1, чтобы продолжить, либо 0 для отмены загрузки." << endl;
	if (EnteringCheckingBool())
	{
		ifstream fin;
		fin.exceptions(ifstream::badbit | ifstream::failbit);
		char check;
		Pipe p1 = {};
		Cs cs1 = {};

		try
		{
			fin.open("data.txt", ios::in);
			//считывание данных
			cout << "Длина трубы:" << endl;
			if (!СheckingIfstream(fin,p1.PipeLength,0.)) {OutputReadingError(); return;}
			cout << "Считано." << endl;
			cout << "Диаметр трубы:" << endl;
			if (!СheckingIfstream(fin, p1.PipeDia,0.)) { OutputReadingError(); return; }
			cout << "Считано." << endl;
			cout << "Статус трубы:" << endl;
			fin >> check;
			if (!СheckingValues(check, fin, '0', '1')) { OutputReadingError(); return;};
			cout << "Считано." << endl;
			cout << "Название КС:" << endl;
			fin>> ws;
			getline(fin, cs1.CsName);
			cout << "Считано." << endl;
			cout << "Количество цехов КС :" << endl;
			if (!СheckingIfstream(fin, cs1.CsWorkshop,0)) { OutputReadingError(); return;}
			cout << "Считано." << endl;
			cout << "Количество рабочих цехов:" << endl;
			if (!СheckingIfstream(fin, cs1.CsWorkingWorkshops,0,cs1.CsWorkshop)) { OutputReadingError(); return;}
			cout << "Считано." << endl;
			cout << "Эффективность КС" << endl;
			if (!СheckingIfstream(fin, cs1.CsEffectiveness,-100,100)) { OutputReadingError(); return;}
			cout << "Считано." << endl;

			fin.close();

			cout << endl << "Данные считаны." << endl;
			cs = cs1;
			p = p1;
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
int MainSharedConsole(unordered_map<int, Pipe>& MapP,Pipe& p,Cs& cs) 
{
	int item =-1;
	do { cin >> item;} while (СheckingValues(item,cin, 0, 7) == false);

	switch (item)
	{
		case 1:
			InputPipe(MapP);
			PauseAndClearing();
			return true;
		case 2:
			InputCs(cs);
			PauseAndClearing();
			return true;
		case 3:
			InformationOutput(p, cs);
			PauseAndClearing();
			return true;
		case 4:
			EditingPipe(p.PipeStatus, p.PipeLength);
			PauseAndClearing();
			return true;
		case 5:
			EditingCs(cs.CsWorkshop, cs.CsWorkingWorkshops);
			PauseAndClearing();
			return true;
		case 6:
			OutputInFile(p, cs);
			PauseAndClearing();
			return true;
		case 7:
			ReadingFromFile(p, cs);
			PauseAndClearing();
			return true;
		case 0:
			if ((p.PipeLength != 0) || (cs.CsWorkshop != 0))
			{
				cout << endl << "Вы хотите сохранить текущее состояние?" <<
					endl << "Введите 1 для сохранения или 0, для выхода из программы." << endl;
				if (EnteringCheckingBool()) { OutputInFile(p, cs);}
				return false;
			}
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
	Pipe p = {};
	Cs cs = {};
	//Запуск консоли
	do { cout << endl; TextSharedConsole();} while (MainSharedConsole(MapP,p, cs) != 0);
}