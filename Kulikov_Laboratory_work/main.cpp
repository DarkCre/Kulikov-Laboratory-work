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
	system("cls"); //https://www.cyberforum.ru/cpp-beginners/thread30713.html?ysclid=l8bdnuacc7726489405
	do
	{
		cout << "������� ����� �����:"<<endl;
		cin >> p.PipeLength;
		if (cin.fail()) //�������� ������������ ������
		{
			cin.clear();//���������� ���� ������
			cin.ignore(1000, '\n');//���������� ����� � ������������� �������
			system("cls"); //������ �������
			cout << "������� ����������� �����, ����������, ��������� �������." << endl;
		}
		else if (p.PipeLength <= 0.)
		{
			system("cls");
			cout << "����� �� ����� ���� ������������� ��� ������ 0, ����������, ��������� �������." << endl;
		}
	} while (cin.fail() || p.PipeLength <= 0.);
}

void InputPipeDia(Pipe& p) //���������� �������� �����
{
	system("cls");
	do
	{
		cout << "������� ������� �����:" << endl;
		cin >> p.PipeDia;
		if (cin.fail())//�������� ������������ ������
		{
			cin.clear();
			cin.ignore(1000, '\n');
			system("cls");
			cout << "������� ����������� �����, ����������, ��������� �������." << endl;
		}
		else if (p.PipeDia <= 0.)
		{
			system("cls");
			cout << "����� �� ����� ���� ������������� ��� ������ 0, ����������, ��������� �������." << endl;
		}
	} while (cin.fail() || p.PipeDia <= 0.);
}

void InputPipeStatus(Pipe& p)//���������� ������� �����
{
	system("cls");
	double check;
	do
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "������� ������ �����(� ������� - 0, � ��������������� ��������� - 1): " << endl;
		cin >> check;
		if (cin.fail() || (check != 0 && check != 1)) //�������� ������������ ������
		{
			system("cls");
			cout << "������� ����������� �����, ����������, ������� 0 ��� 1." << endl;
		}
		p.PipeStatus = check;
	} while (cin.fail() || (check != 0 && check != 1));

}

void InputPipe() //�������������� ����� �������
{
	Pipe p;
	InputPipeLength(p);
	InputPipeDia(p);
	InputPipeStatus(p);
} 

int MainSharedConsole() //������ �������������� ����� �������
{
	int item;
	cin >> item;
	switch (item)
	{
	case 1:
		InputPipe();
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
	bool check = true;
	do
	{
		TextSharedConsole();
		check = MainSharedConsole();
	} while ((check!=0));
}

int main() //����� ����� � ���������
{
	setlocale(LC_ALL, "rus");
	SharedConsole();

	return 0;
}

