#include "WorkingWithGraph.h"


		int InputGraphIDBegin(unordered_map<int, Cs>& MapCs, int ID)
		{
			cout << "������������� �������: " << endl << MapCs << endl;
			cout << "������� ID �������, �� ������� ������� �����: " << endl;

			InputAndCheckingAvailabilityIDToGraph(MapCs, ID);
			while (!MapCs.at(ID).StartWorkshop())
			{
				InputAndCheckingAvailabilityIDToGraph(MapCs, ID);
			}
			return ID;
		}

		int InputGraphIDEnd(unordered_map<int, Cs>& MapCs, int ID, int IDBegin)
		{

			cout << "������� ID �������, � ������� ������ �����: " << endl;
			InputAndCheckingAvailabilityIDToGraph(MapCs, ID);
			int IDEnd = ID;
			bool check = true;
			while (check)
			{
				if (IDBegin == IDEnd)
				{
					cout << "���������� ��������� ���� � �� �� ��! ��������� ������� �����" << endl;
					InputAndCheckingAvailabilityIDToGraph(MapCs, ID);
					IDEnd = ID;
				}
				else
				{
					if (!MapCs.at(ID).StartWorkshop())
					{
						InputAndCheckingAvailabilityIDToGraph(MapCs, ID);
						IDEnd = ID;
					}
					else
						break;

				}
			}
			return IDEnd;
		}

			void Re_enteringOrCreating(unordered_map<int, Pipe>& MapP, unordered_map<int, Cs>& MapCs, forward_list<int>& D500, forward_list<int>& D700, forward_list<int>& D1400)
		{
			cout << "���� ��� ���������� �� �������. �� ������ �������� ����� �����?" << endl;
			cout << "������� 1 ��� �������� ��� 0 ��� ���������� ����� �������." << endl;
			if (EnteringCheckingBool())
			{
				CreatingPipe(MapP, D500, D700, D1400);
			}
		}
	
		int InputGraphIDPipe(unordered_map<int, Pipe>& MapP, unordered_map<int, Cs>& MapCs, forward_list<int>& D500, forward_list<int>& D700, forward_list<int>& D1400)
		{
			while (true)
			{
				cout << "����� ��������� ������� ��?" << endl;
				cout << "�������:" << endl
					<< "1, ���� ������� ����� = 500" << endl
					<< "2, ���� ������� ����� = 700" << endl
					<< "3, ���� ������� ����� = 1400" << endl;
				int item = IntInput(1, 3);

				if ((item == 1 && D500.empty()) || (item == 2 && D700.empty()) || (item == 3 && D1400.empty()))
					Re_enteringOrCreating(MapP, MapCs, D500, D700, D1400);
				else
				{
					int Id;
					if (item == 1)
					{
						Id = D500.front();
						D500.pop_front();
					}
					else if (item == 2)
					{
						Id = D700.front();
						D700.pop_front();
					}
					else
					{
						Id = D1400.front();
						D1400.pop_front();
					}
					return Id;
				}

			}
		}

	void AddingAnEdgeToGraph(unordered_map<int, Pipe>& MapP, unordered_map<int, Cs>& MapCs, forward_list<int>& D500, forward_list<int>& D700, forward_list<int>& D1400, unordered_map<int, pair <int, int>>& Graph)
	{

		int ID=0;
		int IDBegin = InputGraphIDBegin(MapCs,ID);
		int IDEnd = InputGraphIDEnd(MapCs, ID,IDBegin);
		int IDPipe = InputGraphIDPipe(MapP, MapCs, D500, D700, D1400);
	
		Graph.emplace(IDPipe, pair<int, int>(IDBegin, IDEnd));

	}

	int SummCollumn(int n,int i, vector<vector<int>> AdjacencyMatrix)
	{
		int Summ = 0;
		for (int j = 1; j < n+2; ++j)
		{
			Summ+=AdjacencyMatrix[j][i];
		}
		return Summ;
	}

	int GraphManagementConsole(unordered_map<int, Pipe>& MapP, unordered_map<int, Cs>& MapCs, forward_list<int>& D500, forward_list<int>& D700, forward_list<int>& D1400, unordered_map<int, pair <int, int>>& Graph)
	{
		int item = IntInput(0, 4);

		switch (item)
		{
		case 1:
		{
			if (!CheckingFulfillmentConditionsToGraph(MapCs))
				return false;
		
			AddingAnEdgeToGraph(MapP, MapCs, D500, D700, D1400, Graph);

			PauseAndClearing();
			return true;
		}
		case 2:

			PauseAndClearing();
			return true;
		case 3:
		{
			//������� ID ��, ����� �������� ���� ���� �� ���� �����
			set<int> IDCsGraph;

			if (Graph.size() == 0)
			{
				cout << "���������� ������� ���� �� ���� ���������� ��!";
				return false;
			}
			for (const auto& elem : Graph)
			{
				IDCsGraph.emplace(elem.second.first);
				IDCsGraph.emplace(elem.second.second);
			}

			int n = (int)IDCsGraph.size();
			//�������� ��������� ��� ������� ���������
			vector<vector<int>> AdjacencyMatrix = {vector<int>(n+1,0)};
			
			auto it = IDCsGraph.begin();
			for (int i = 1;  i < n+1; ++i,++it)
			{
				AdjacencyMatrix[0][i] = *it;
			}
			it = IDCsGraph.begin();
			for (int i = 0; i<n; ++i,++it)
			{
				vector<int> row{ *it };
				int k = 0;
				while (k != n)
				{
					row.push_back(0);
					++k;
				}
				AdjacencyMatrix.push_back(row);
			}

			//���������� ������� ��������� 
			for (const auto& elem : Graph)
			{
				for (int i = 1; i < n + 1; ++i)
				{
					if (AdjacencyMatrix[0][i] == elem.second.second)
					{
						for (int j = 1; j < n + 1; ++j)
						{
							if (AdjacencyMatrix[j][0] == elem.second.first)
							{
								AdjacencyMatrix[j][i] = elem.first;
							}
						}
					}
				}
			}

			//����� ������� ���������
			cout << "������� ���������:" << endl;
			for (const auto& row : AdjacencyMatrix)
			{
				for (const auto& item : row)
				{
					cout << ' ' << ' ' << item;
				}
				cout << endl;
			}


			AdjacencyMatrix.push_back(vector<int>(n + 1, -1));

			//�������� ������� �������������� ����������
			//stack<int> SortingResult;
			queue<int> SortingResult;
			int k = 0;
			while (k < n + 1 && SortingResult.size() != n)
			{
				for (int i = 1; i < n + 1; ++i)
				{
					if (SummCollumn(n, i, AdjacencyMatrix) == -1)
					{
						SortingResult.push(AdjacencyMatrix[0][i]);
						AdjacencyMatrix[n + 1][i]=0;
						for (int j = 1; j < n + 1; ++j)
						{
							AdjacencyMatrix[i][j] = 0;
						}
						break;
					}
				}
			++k;
			}
			if (k >= n + 1)
			{
				cout << "�������������� ���������� ��� ���������� ����� ����������!"<<endl;
				return 0;
			}

			//����� ����� � �������
			cout << endl;
			while (SortingResult.size() > 0)
			{
				cout<<SortingResult.front()<< " ";
				SortingResult.pop();
			}
			cout << endl;

			PauseAndClearing();
			return true;
		}
		case 4:
			GraphOutput(cout,Graph,MapP);
			PauseAndClearing();
			return true;
		case 0:
			return false;
		}

		return true;
	}

void WorkingWithGraph(unordered_map<int, Pipe>& MapP, unordered_map<int, Cs>& MapCs, forward_list<int>& D500, forward_list<int>& D700, forward_list<int>& D1400, unordered_map<int, pair <int, int>>& Graph)
{

	do {
		cout << endl;
		cout << " ���� ������ � ������ ���������������� ����: " << endl
			<< "1. ��������� ��" << endl
			<< "2. ������� ����� ����� ��" << endl
			<< "3. �������� �������������� ����������" << endl
			<< "4. ������� ���������� �� ���������� ��"<<endl
			<< "0. ����� � ������� ����" << endl << endl;
	} while (GraphManagementConsole(MapP, MapCs, D500, D700, D1400, Graph) != 0);
}
