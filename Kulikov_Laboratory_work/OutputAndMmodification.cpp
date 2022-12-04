#include "OutputAndMmodification.h"

//���� ��������� �����
string EnteringFragmentName()
{
	string Name = "NoName";
	do
	{
		cout << "������� �������� �������� ������� ��������." << endl << "������: ";
		cin >> ws;
		getline(cin, Name);
	} while (!CheckingString(Name));
	return Name;
}
//���� ����� �����
string EnteringFileName()
{
	cout << endl << "������� ��� �����: " << endl;
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

//���������� ��� ��
template<typename T>
void ChangingObjectsCs(unordered_map<int, Cs>& MapCs, Filter<T, Cs> f, T param)
{
	unordered_map<int, int> IDs;
	FilterResults(MapCs, IDs, f, param);
}

//����� ���������� �� ���������
void InformationOutput(const unordered_map<int, Pipe>& MapP, unordered_map<int, Cs>& MapCs) //����� ���������� �� ����� � ��
{
	string Name = "NoName";
	double Effectiveness = 0;
	bool Status = false;
	int SizeCs = MapCs.size();
	cout << "1. ������� ���������� �� ���� ������" << endl
		<< "2. ������� ���������� �� ���� ��" << endl
		<< "3. ������� ���������� �� ���� ��������" << endl
		<< "4. ������� ���������� �� ������� �������� ��" << endl
		<< "5. ������� ���������� �� ������� �������� ����������������� ����� ��" << endl
		<< "0. ��� �������� � ������� ����." << endl << endl;

	int item = IntInput(0, 7);

	switch (item)
	{
	case 1:
		cout << "�����: " << endl << MapP;
		return;
	case 2:
		cout << "������������� �������: " << endl << MapCs;
		return;
	case 3:
		cout << "�����: " << endl << MapP;
		cout << "������������� �������: " << endl << MapCs;
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
			cout << "������� ������� ����������������� ����� (�� 0 �� 100): " << endl;
			cin >> Effectiveness;
		} while (!�heckingValues(Effectiveness, cin, 0., 100.));

		ChangingObjectsCs(MapCs, CheckByEffectiveness, Effectiveness);
		return;
	case 0:
		return;
	}
	return;

}

//��������� ��������	
template<typename T>
using FilterEditing = void(*)(T&, unordered_set<int>&);
//������������ �������������� ������ ����
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

//�������� �������������� �������
void BatchEditingPipes(unordered_map<int, Pipe>& MapP, unordered_set<int>& SetP)
{
	cout << "������� ����� ������ ����� (� ������� - 0, � ��������������� ��������� - 1)" << endl;
	int Status = IntInput(0, 1);
	for (const auto& elem : SetP)
	{
		MapP.at(elem).SetStatus(Status);
	}
}

//��������  ��������
template<typename T>
void BatchErasePipes(T& Obj, unordered_set<int>& SetP)
{
	for (const auto& elem : SetP)
	{
		Obj.erase(elem);
	}
}


//����� �������� � ����������
template<typename T>
void SelectingAnEditAction(T& Obj, unordered_set<int>& SetP, FilterEditing<T> f)
{
	cout << endl << "������� 1 ��� �������������� �������� ��� 0 ��� ��������." << endl;
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

//�������� Set �� ���� ��������� �������
void SelectingAllFilterElements(unordered_map<int, int>& IDs, unordered_set<int>& SetP)
{
	for (const auto& elem : IDs)
	{
		SetP.emplace(elem.second);
	}
}
//��� ���������� ������� ��� ��������������� 
void EnteringIDChange(unordered_map<int, int>& IDs, unordered_set<int>& SetP)
{
	int Number = 0;
	cout << "������� -1 ��� ����, ��� �� ������� ��� ���������� �������" << endl
		<< "��� ������� ����� Enter ������ �� ������ ������������ ��� ��������." << endl
		<< "��� ���������� ����� ������� 0" << endl;

	Number = IntInput(-1, IDs.size());
	while (Number != 0 && Number != -1)
	{
		SetP.emplace(IDs.at(Number));
		Number = IntInput(0, IDs.size());
	}
	if (Number == 0 && SetP.size() == 0) { return; }
	if (Number == -1) { SelectingAllFilterElements(IDs, SetP); }
}
//���������� ����������
template<typename T, typename T1>
void FilterResults(unordered_map<int, T1>& Obj, unordered_map<int, int>& IDs, Filter<T, T1> f, T param)
{
	int count = 0;
	for (const auto& elem : Obj)
	{
		if (f(elem.second, param))
		{
			++count;
			cout << "����� � ������: " << count << endl;
			cout << "ID �������: " << elem.first << endl << elem.second << endl;
			IDs.emplace(count, elem.first);
		}
	}
	if (count == 0)
	{
		cout << "������� �������� �� �������!" << endl;
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

//���� ID ��� ����������� ��������������
template<typename T>
void InputSetP(unordered_map<int, T>& Obj, unordered_set<int>& SetP)
{
	cout << "������� ����� Enter ID ��������, ������� ����� ��������." << endl
		<< "��� ���������� ����� ������� 0" << endl;
	int ID;
	InputAndCheckingAvailabilityID(Obj, ID);
	while (ID != 0)
	{
		SetP.emplace(ID);
		InputAndCheckingAvailabilityID(Obj, ID);
	}
	cout << endl;
}

//��������� ��������
template<typename T>
void ChangingObjectsPipe(unordered_map<int, Pipe>& MapP, Filter<T, Pipe> f, T param)
{
	unordered_map<int, int> IDs;
	FilterResults(MapP, IDs, f, param);
	unordered_set<int> SetP;
	EnteringIDChange(IDs, SetP);

	SelectingAnEditAction(MapP, SetP, BatchEditingPipes);
}

//��������� ��������
void ChangingObjects(unordered_map<int, Pipe>& MapP, unordered_map<int, Cs>& MapCs)
{
	string Name = "NoName";
	unordered_set<int> SetObj;
	bool Status = false;
	int SizePipes = MapP.size();
	int SizeCs = MapCs.size();
	cout << "1. �������������� �� ������� �������� ����" << endl
		<< "2. �������������� �� ������� ������� �����" << endl
		<< "3. �������������� �� ID ����" << endl
		<< "4. �������������� �� ID ��" << endl
		<< "0. ��� �������� � ������� ����." << endl << endl;

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
		cout << "������� 1, ���� ������ ������� ���� '� ������' ��� 0, ���� �� ������ '� �������'" << endl;
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

