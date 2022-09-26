#include <iostream> //���������� ���������� ��� ������ � ������ � ������� (# - �������� ��� ��� ������ ��� ����� � ������������).
using namespace std; //��������� �� ��������� ����������� ������������ ��� (std), ��� ����, ��� �� �� ��������� ����� ���������� ������� ������������ ������ ���.

struct Pipe //�������� ��������� �����
{
	double PipeLength; // ����� �����
	double PipeDia;   //  ������� �����
	bool PipeStatus; //   ������ ����� (� ������� ��� ���)
}; 

struct �s //�������� ��������� ������������� �������
{
	string CsName; //��� ��
	int CsWorkshop; //���������� ����� ��
	int CsWorkingWorkshops; //���������� ���������� ����� ��
	double Effectiveness; //������������� ��
};

bool CheckingPositiveDouble(const double& Double) //�������� �� ������������ ����� ������������� ���������� ���� double
{
	if (cin.fail()|| cin.peek() != '\n') //�������� ������������ ������
	{
		cin.clear();//���������� ���� ������
		cin.ignore(1000, '\n');//���������� ����� � ������������� �������
		cout << "������� ����������� �����, ����������, ��������� �������." << endl;
		return 0;
	}
	else if (Double <= 0.)
	{
		cout << "��� �������� �� ����� ���� ������������� ��� ������ 0, ����������, ��������� �������." << endl;
		return 0;
	}
	return 1;
}


bool CheckingBool(const bool& Bool) //�������� �� ������������ ����� ���������� ���� bool
{
	if (cin.fail() || cin.peek() != '\n' || (Bool != 0 && Bool != 1)) //�������� ������������ ������
	{
		cin.clear();//���������� ���� ������
		cin.ignore(1000, '\n');//���������� ����� � ������������� �������
		cout << "������� ����������� �����, ����������, ������� 0 ��� 1." << endl;
		return 0;
	}
	return 1;
}

void TextSharedConsole() //��������� ����� �������
{
	cout<< "1. �������� �����" << endl
		<< "2. �������� ��" << endl
		<< "3. �������� ���� ��������" << endl
		<< "4. ������������� �����" << endl
		<< "5. ������������� ��" << endl
		<< "6. ���������" << endl
		<< "7. ���������" << endl
		<< "0. �����" << endl;
}



void InputPipeLength(Pipe& p) //���������� ����� �����
{
	do
	{
		cout << "������� ����� �����:"<<endl;
		cin >> p.PipeLength;
	} while (CheckingPositiveDouble(p.PipeLength)==false);
}

void InputPipeDia(Pipe& p) //���������� �������� �����
{
	do
	{
		cout << "������� ������� �����:" << endl;
		cin >> p.PipeDia;
		
	} while (CheckingPositiveDouble(p.PipeDia)==false);
}

void InputPipeStatus(Pipe& p)//���������� ������� �����
{
	do
	{
		cout << "������� ������ �����(� ������� - 0, � ��������������� ��������� - 1): " << endl;
		cin >> p.PipeStatus;
	} while (CheckingBool(p.PipeStatus)==false);
}


void InputPipe(Pipe& p) //������������������ ����� ������ �� �����
{
	double check;
	if (p.PipeLength != 0)
	{
		cout << "�� ������� ��� ������ ������������ ������ �� �����?" << endl << "������� 1 ��� ������������� ��������" << endl;
		cin >> check;
		if (check == true)
		{
			cout << "�������� �����" << endl;
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
		cout << "�������� �����" << endl;
		InputPipeLength(p);
		InputPipeDia(p);
		InputPipeStatus(p);
	}

} 


int MainSharedConsole(Pipe& p) //������ �������������� ����� �������
{
	int item;
	cin >> item;
	switch (item)
	{
	case 1:
		InputPipe(p);
		break;
	case 2:
		cout << "2. �������� ��";
		break;
	case 3:
		cout << "3. �������� ���� ��������";
		break;
	case 4:
		cout << "4. ������������� �����";
		break;
	case 5:
		cout << "5. ������������� ��";
		break;
	case 6:
		cout << "6. ���������";
		break;
	case 7:
		cout << "7. ���������";
		break;
	case 0:
		return 0;
		break;
	}
}


void SharedConsole() //������� �������
{
	Pipe p = {};
	bool check = true;
	do
	{
		TextSharedConsole();
		check = MainSharedConsole(p);
	} while ((check!=0));
}


int main() //����� ����� � ���������
{
	setlocale(LC_ALL, "rus");
	SharedConsole();

	return 0;
}

