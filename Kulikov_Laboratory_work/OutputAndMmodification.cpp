#include "OutputAndMmodification.h"

//Ввод фрагмента имени
string EnteringFragmentName()
{
	string Name = "NoName";
	do
	{
		cout << "Введите фрагмент названия искомых объектов." << endl << "Фильтр: ";
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

//Фильтрация для КС
template<typename T>
void ChangingObjectsCs(unordered_map<int, Cs>& MapCs, Filter<T, Cs> f, T param)
{
	unordered_map<int, int> IDs;
	FilterResults(MapCs, IDs, f, param);
}

//Вывод информации по элементам
void InformationOutput(const unordered_map<int, Pipe>& MapP, unordered_map<int, Cs>& MapCs) //вывод информации по трубе и КС
{
	string Name = "NoName";
	double Effectiveness = 0;
	bool Status = false;
	int SizeCs = MapCs.size();
	cout << "1. Вывести информацию по всем трубам" << endl
		<< "2. Вывести информацию по всем КС" << endl
		<< "3. Вывести информацию по всем объектам" << endl
		<< "4. Вывести информацию по фильтру название КС" << endl
		<< "5. Вывести информацию по фильтру процента незадействованных цехов КС" << endl
		<< "0. Для возврата в главное меню." << endl << endl;

	int item = IntInput(0, 7);

	switch (item)
	{
	case 1:
		cout << "Трубы: " << endl << MapP;
		return;
	case 2:
		cout << "Компрессорные станции: " << endl << MapCs;
		return;
	case 3:
		cout << "Трубы: " << endl << MapP;
		cout << "Компрессорные станции: " << endl << MapCs;
		return;
	case 4:
		if (!CheckingPresenceElements(cout, SizeCs)) { return; }

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
template<typename T, typename T1>
void FilterResults(unordered_map<int, T1>& Obj, unordered_map<int, int>& IDs, Filter<T, T1> f, T param)
{
	int count = 0;
	for (const auto& elem : Obj)
	{
		if (f(elem.second, param))
		{
			++count;
			cout << "Номер в списке: " << count << endl;
			cout << "ID объекта: " << elem.first << endl << elem.second << endl;
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
void InputAndCheckingAvailabilityID(unordered_map<int, T>& Obj, int& ID)
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
	InputAndCheckingAvailabilityID(Obj, ID);
	while (ID != 0)
	{
		SetP.emplace(ID);
		InputAndCheckingAvailabilityID(Obj, ID);
	}
	cout << endl;
}

//Изменение объектов
template<typename T>
void ChangingObjectsPipe(unordered_map<int, Pipe>& MapP, Filter<T, Pipe> f, T param)
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
	cout << "1. Редактирование по фильтру названия труб" << endl
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

