#include "WorkingWithGraph.h"
#include <set>

		int InputGraphIDBegin(unordered_map<int, Cs>& MapCs, int ID)
		{
			cout << "Компрессорные станции: " << endl << MapCs << endl;
			cout << "Введите ID станции, из которой выходит труба: " << endl;

			InputAndCheckingAvailabilityIDToGraph(MapCs, ID);
			while (!MapCs.at(ID).StartWorkshop())
			{
				InputAndCheckingAvailabilityIDToGraph(MapCs, ID);
			}
			return ID;
		}

		int InputGraphIDEnd(unordered_map<int, Cs>& MapCs, int ID, int IDBegin)
		{

			cout << "Введите ID станции, в которую входит труба: " << endl;
			InputAndCheckingAvailabilityIDToGraph(MapCs, ID);
			int IDEnd = ID;
			bool check = true;
			while (check)
			{
				if (IDBegin == IDEnd)
				{
					cout << "Невозможно соединить одну и ту же КС! Повторите попытку ввода" << endl;
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
			cout << "Труб для соединения не найдено. Вы хотите добавить новую трубу?" << endl;
			cout << "Введите 1 для создания или 0 для повторного ввода размера." << endl;
			if (EnteringCheckingBool())
			{
				CreatingPipe(MapP, D500, D700, D1400);
			}
		}
	
		int InputGraphIDPipe(unordered_map<int, Pipe>& MapP, unordered_map<int, Cs>& MapCs, forward_list<int>& D500, forward_list<int>& D700, forward_list<int>& D1400)
		{
			while (true)
			{
				cout << "Каким диаметром связать КС?" << endl;
				cout << "Введите:" << endl
					<< "1, если диаметр трубы = 500" << endl
					<< "2, если диаметр трубы = 700" << endl
					<< "3, если диаметр трубы = 1400" << endl;
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
			set<int> IDCsGraph;

			if (Graph.size() == 0)
			{
				cout << "Необходимо создать хотя бы одно соединение КС!";
				return false;
			}
			for (const auto& elem : Graph)
			{
				IDCsGraph.emplace(elem.second.first);
				IDCsGraph.emplace(elem.second.second);
			}

			int n = (int)IDCsGraph.size();
			vector<vector<int>> AdjacencyMatrix = {vector<int>(n+1,0)};
			/*AdjacencyMatrix.reserve(n);*/
			
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

			for (const auto& row : AdjacencyMatrix) 
			{
				for (const auto& item : row) 
				{
					cout << ' ' << item;
				}
				cout << endl;
			}

			/*for (int i = 0; i < n; ++i)
			{
				for (int j = 0; i < n; ++i)
				{
					
				}
			}*/


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
		cout << " Меню работы с графом газотранспортной сети: " << endl
			<< "1. Соединить КС" << endl
			<< "2. Удалить трубу между КС" << endl
			<< "3. Провести топологическую сортировку" << endl
			<< "4. Вывести информацию по соеденённым КС"<<endl
			<< "0. Выход в Главное меню" << endl << endl;
	} while (GraphManagementConsole(MapP, MapCs, D500, D700, D1400, Graph) != 0);
}
