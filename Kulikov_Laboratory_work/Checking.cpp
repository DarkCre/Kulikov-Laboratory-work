#include "Checking.h"

void PauseAndClearing()
{
	cout << endl << "������� ����� ������� ��� �������� � ����." << endl;
	_getch();
	system("cls");
}

bool EnteringCheckingBool()
{
	char ch;
	do
	{
		cin >> ch;
	} while (!�heckingValues(ch, cin, '0', '1'));
	if (ch == '1')
	{
		return true;
	}
	return false;
}

bool CheckingString(string S)
{
	int i = 0;
	while ( i != S.size()) {
		if (!(S[i] >= 'A' && S[i] <= 'z') && !(S[i] == ' ') && !(S[i]>='0' && S[i]<='9') )
		{
			cout<<"� ����� ������ ���� ������ ��������� ����� ��� �����."<<endl;
			return false;
		}
		++i;
	}
	return true;
}

//�������� �� �������������
bool CheckByEffectiveness(const Cs& Cs, double param)
{
	double Workshop = Cs.GetWorkshop();
	double WorkingWorkshops = Cs.GetWorkingWorkshops();
	double Effectiveness = param / 100;
	return((1 - WorkingWorkshops / Workshop) >= Effectiveness);
}

//�������� �������� �� ������
bool CheckByStatus(const Pipe& P, bool param)
{
	return(P.GetStatus() == param);
}

//���� ����
int IntInput(int beginning, int end)
{
	int item;
	do
	{
		cin >> item;
	} while (�heckingValues(item, cin, beginning, end) == false);
	return item;
}

bool CheckingFulfillmentConditionsToGraph(const unordered_map<int, Cs>& MapCs)
{
	int k = 0;
	for (const auto& elem : MapCs)
	{
		if (elem.second.GetWorkingWorkshops() != elem.second.GetWorkshop())
			++k;
	}
	if (MapCs.size() < 2 || k < 2)
	{
		cout << "��� ���������� �� ���������� �� ����� 2� �� � ����������� ����� �������, ��� ������������!" << endl;
		return false;
	}
	return true;
}