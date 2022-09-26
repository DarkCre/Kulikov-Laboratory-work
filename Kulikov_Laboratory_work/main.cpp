#include <iostream> //���������� ���������� ��� ������ � ������ � ������� (# - �������� ��� ��� ������ ��� ����� � ������������).
#include <conio.h> // ���������� ��� ��������, �� ������� �������
#include <fstream>// ���� � ���� � ����� �� �����
using namespace std; //��������� �� ��������� ����������� ������������ ��� (std), ��� ����, ��� �� �� ��������� ����� ���������� ������� ������������ ������ ���.

//��� ���������
struct Pipe //�������� ��������� �����
{
	double PipeLength; // ����� �����
	double PipeDia;   //  ������� �����
	bool PipeStatus; //   ������ ����� (� ������� ��� ���)
}; 

struct Cs //�������� ��������� ������������� �������
{
	string CsName; //�������� ��
	int CsWorkshop; //���������� ����� ��
	int CsWorkingWorkshops; //���������� ���������� ����� ��
	int CsEffectiveness; //������������� ��
};

//�������� ����� ������ ����� ������
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

bool CheckingIntRange(const int& Int, const int& beginning,const int& end) //�������� �� ������������ ����� ���������� ���� int � ��������� ���������
{
	if (cin.fail() || cin.peek() != '\n' || Int<beginning || Int>end)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "������� ����������� �����, ����������, ������� ����� ����� �� " << beginning << " �� " << end << endl << endl;
		return 0;
	}
	return 1;
}

bool CheckingInt(const int& Int) //�������� �� ������������ ����� ���������� ���� int
{
	if (cin.fail() || cin.peek() != '\n')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "������� ����������� ������, ����������, ������� ����� �����"<< endl;
		return 0;
	}
	return 1;
}


//����� ������� �������
void TextSharedConsole() //��������� ����� �������
{
	cout<<"������� ����"<<endl
		<<"1. �������� �����" << endl
		<< "2. �������� ��" << endl
		<< "3. �������� ���� ��������" << endl
		<< "4. ������������� �����" << endl
		<< "5. ������������� ��" << endl
		<< "6. ���������" << endl
		<< "7. ���������" << endl
		<< "0. �����" << endl << endl;
}


//���� ���������� �����
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

//���� �����
void InputPipe(Pipe& p) //������ �� ���������� ���� ������ �� ����� � ������������������ �� ����� 
{
	double check=0;
	if (p.PipeLength != 0)
	{
		cout << "�� ������� ��� ������ ������������ ������ �� �����?" << endl << "������� 1 ��� ������������� ��������" << endl;
		cin >> check;
		if (check == 1)
		{
			cout << "�������� �����:" << endl << endl;
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
		cout << "�������� �����:" << endl << endl;
		InputPipeLength(p);
		InputPipeDia(p);
		InputPipeStatus(p);
	}

} 

//���� ���������� ��
void InputCsName(Cs& cs) //���������� ����� ��
{
	cout << "������� �������� ������������� �������" << endl;
	cin >> cs.CsName;
}

void InputCsWorkshop(Cs& cs) //���������� ���������� ����� ��
{
	do
	{
		cout << "������� ���������� ����� ������������� �������" << endl;
		cin >> cs.CsWorkshop;
		if (cs.CsWorkshop <= 0)
		{
			cout << "����� ������ ���� �� ������ 1, ����������, ��������� ������� �����." << endl;
		}
	} while (CheckingInt(cs.CsWorkshop) == false || cs.CsWorkshop <= 0);
}

void InputCsWorkingWorkshops(Cs& cs) //���������� ���������� ������� ����� ��
{
	do
	{
		cout << "������� ���������� ���������� �����" << endl;
		cin >> cs.CsWorkingWorkshops;
	} while (CheckingIntRange(cs.CsWorkingWorkshops,0,cs.CsWorkshop) == false);
}

void InputCsEffectiveness(Cs& cs) //���������� ������������� ��
{
	do
	{
		cout << "������� ������������� �������:" << endl;
		cin >> cs.CsEffectiveness;
	} while (CheckingIntRange(cs.CsEffectiveness,-100,100) == false);
}

//���� ��
void InputCs(Cs& cs) //������ �� ���������� ���� ������ �� ������������� ������� � ������������������ �� �����
{
	double check=0;
	if (cs.CsWorkshop != 0)
	{
		cout << "�� ������� ��� ������ ������������ ������ �� ������������� �������?" << endl << "������� 1 ��� ������������� ��������" << endl;
		cin >> check;
		if (check == 1)
		{
			cout << "�������� ������������� �������: " << endl << endl;
			InputCsName(cs);
			InputCsWorkshop(cs);
			InputCsWorkingWorkshops(cs);
			InputCsEffectiveness(cs);
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
		cout << "�������� ������������� �������:" << endl << endl;
		InputCsName(cs);
		InputCsWorkshop(cs);
		InputCsWorkingWorkshops(cs);
		InputCsEffectiveness(cs);
	}

}

//���������� �� ���������
void InformationOutput(const Pipe& p, const Cs& cs) //����� ���������� �� ����� � ��
{
	cout << "���������� �� �����:" << endl;
	if (p.PipeLength != 0)
		cout << endl << "����� �����: " <<p.PipeLength<< endl << "������� �����: " <<p.PipeDia<< endl << "������ �����: "<< (p.PipeStatus==true ? "� ������":"� �������") << endl;
	else
	{
		cout << "������ �� �������. ������� ���������� ������� �����." << endl;
	}

	cout << endl << "���������� �� ������������� �������:" << endl;
	if (cs.CsWorkshop != 0)
	{
		cout << endl << "��������: " << cs.CsName << endl << "���������� �����: " << cs.CsWorkshop << endl << "���������� ����� � ������: " << cs.CsWorkingWorkshops << endl << "�������������: " << cs.CsEffectiveness<< endl;
		_getch();//https://www.youtube.com/watch?v=6tGgasGBgmc - ������� �������� ������� ����� ������� 
	}
	else
	{
		cout << "������ �� �������. ������� ���������� ������� ������������� �������." << endl;
		_getch();
	}
}

//�������������� �����
void EditingPipe(bool& PipeStatus) //�������������� �����
{
	cout << endl << "�������������� �����:" << endl;
	do
	{
		cout << "������� ���������� ������ �����(� ������� - 0, � ��������������� ��������� - 1): " << endl;
		cin >> PipeStatus;
	} while (CheckingBool(PipeStatus) == false);
	cout << endl << "������ ���������." << endl;
}

//�������������� �� (�������������� �����)
bool FunctionalPartEditingCs(Cs& cs, const int& item) //�������������� ����� ��������� ��
{
	int check1;
	int check2;
	check1 = cs.CsWorkingWorkshops + 1;
	check2 = cs.CsWorkingWorkshops - 1;
	if (check1 > cs.CsWorkshop && item==1)
	{
		cout << "���������� ��������� � ������ ������ �����, ��� ����������. ����������, ��������� ������� �����." << endl;
		return 0;
	}
	else if (item == 1)
	{
		cs.CsWorkingWorkshops++;
		cout << endl << "������ ���������." << endl;
		return 1;
	}
	else if (item == 0)
	{
		return 1;
	}
	else if (check2 < 0 && item == -1)
	{
		cout << "���������� ��������� ���������� ���������� �����, �.�. ��� ���� �� ������ ������ �����������." << endl;
		return 0;
	}
	else if (item == -1)
	{
		cs.CsWorkingWorkshops--;
		cout << endl << "������ ���������." << endl;
		return 1;
	}
}
//�������������� �� (����� � ����)
void EditingCs(Cs& cs) //���������� ����� �������������� ��
{	
int item;
	cout << endl << "�������������� ������������� �������:" << endl
				 <<"�� ������ ������ ����� � ������: "<< cs.CsWorkingWorkshops << endl << endl;
	do
	{
		do
		{
			cout << "������� 1 - ��� ���������� ���������� ���������� ����� �� 1." << endl
				<< "������� 0 - ��� �������� � ������� ����." << endl
				<< "������� -1 - ��� ���������� ���������� ���������� ����� �� 1." << endl;
			cin >> item;
		} while (CheckingIntRange(item, -1, 1) == false);
	
	} while (FunctionalPartEditingCs(cs,item) == false);
}

//����� � ����
void OutputInFile(const Pipe& p, const Cs& cs)
{
	ofstream fout;
	fout.open("data.txt", ios::out);
	if (fout.is_open())
	{
		fout << p.PipeLength << endl << p.PipeDia << endl << p.PipeStatus << endl;
		fout << cs.CsName << endl << cs.CsWorkshop << endl << cs.CsWorkingWorkshops << endl << cs.CsEffectiveness << endl;
		fout.close();
		cout << "������ ���������." << endl;
	}
	else
	{
		cout << "�� ������� ������� ����.";
	}
}

//���������� �� �����
void ReadingFromFile(Pipe& p, Cs& cs)
{
	ifstream fin;
	fin.open("data.txt", ios::in);
	if (fin.is_open())
	{
		fin >> p.PipeLength;
		fin >> p.PipeDia;
		fin >> p.PipeStatus;
		fin >> cs.CsName;
		fin >> cs.CsWorkshop;
		fin >> cs.CsWorkingWorkshops;
		fin >> cs.CsEffectiveness;
		fin.close();
		cout << "������ �������." << endl;
	}
	else
	{
		cout << "�� ������� ������� ����.";
	}
}

//������� �������
int MainSharedConsole(Pipe& p, Cs& cs) //������ �������������� ����� �������
{
	int item;
	do
	{
		cin >> item;
	} while (CheckingIntRange(item, 0, 7) == false);
	
	switch (item)
	{
	case 1:
		InputPipe(p);
		break;
	case 2:
		InputCs(cs);
		break;
	case 3:
		InformationOutput(p, cs);
		break;
	case 4:
		if (p.PipeLength != 0)
		{
			EditingPipe(p.PipeStatus);
		}
		else
		{
			cout << "������ �� �������� ���������������. ������� ���������� ������� �����." << endl;
			_getch();
		}
		break;
	case 5:
		if (cs.CsWorkshop != 0)
		{
			EditingCs(cs);
		}
		else
		{
			cout << "������ �� �������� ���������������. ������� ���������� ������� ������������� �������." << endl;
			_getch();
		}
		break;
	case 6:
		OutputInFile(p, cs);
		break;
	case 7:
		ReadingFromFile(p, cs);
		break;
	case 0:
		return 0;
		break;
	}
}

void SharedConsole() //������� �������
{
	Pipe p = {};
	Cs cs = {};
	bool check = true;
	do
	{
		cout << endl;
		TextSharedConsole();
		check = MainSharedConsole(p,cs);
	} while ((check!=0));
}



int main() //����� ����� � ���������
{
	setlocale(LC_ALL, "rus");
	SharedConsole();

	return 0;
}

