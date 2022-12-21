#include "WorkingWithGraph.h"
#include "Ford_Fulkerson.h"


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

			void Re_enteringOrCreating(unordered_map<int, Pipe>& MapP, unordered_map<int, Cs>& MapCs, forward_list<int>& FreePipes)
		{
			cout << "Труб для соединения не найдено. Вы хотите добавить новую трубу?" << endl;
			cout << "Введите 1 для создания или 0 для повторного ввода размера." << endl;
			if (EnteringCheckingBool())
			{
				CreatingPipe(MapP, FreePipes);
			}
		}
	
		int InputGraphIDPipe(unordered_map<int, Pipe>& MapP, unordered_map<int, Cs>& MapCs, forward_list<int>& FreePipes)
		{
			while (true)
			{
				cout << "Каким диаметром связать КС?" << endl;

				double check;
				int id = 0;
				do
				{
					cin >> check;
				} while (!СheckingValues(check, cin, 0.0001));
				
				auto it0 = FreePipes.begin();
				auto it1 = FreePipes.begin();
				bool remfl = false;
				while (it1 != FreePipes.end()) {
					if (MapP.at(*it1).GetDia() == check)
					{
						id = *it1;
						if (it1 == FreePipes.begin())
							FreePipes.pop_front();
						else
							FreePipes.erase_after(it0);
						remfl = true;
						break;
					}
					it0 = it1++;
				}

				if (id==0)
					Re_enteringOrCreating(MapP, MapCs, FreePipes);
				else
					return id;

			}
		}

	void AddingAnEdgeToGraph(unordered_map<int, Pipe>& MapP, unordered_map<int, Cs>& MapCs, forward_list<int>& FreePipes, unordered_map<int, pair <int, int>>& Graph)
	{

		int ID=0;
		int IDBegin = InputGraphIDBegin(MapCs,ID);
		int IDEnd = InputGraphIDEnd(MapCs, ID,IDBegin);
		int IDPipe = InputGraphIDPipe(MapP, MapCs, FreePipes);
	
		Graph.emplace(IDPipe, pair<int, int>(IDBegin, IDEnd));

	}

			void OutputAdjacencyMatrix(vector<vector<int>>& AdjacencyMatrix)
	{
		//вывод матрицы смежности
		cout << "Матрица смежности:" << endl;
		for (const auto& row : AdjacencyMatrix)
		{
			for (const auto& item : row)
			{
				cout << ' ' << ' ' << item;
			}
			cout << endl;
		}
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

		bool SelectionOfTheCSGraphID(const unordered_map<int, pair <int, int>>& Graph, set<int>& IDCsGraph)
		{
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
			return true;
		}

		void CreatingAndFillingInTheAdjacencyMatrix(const unordered_map<int, pair <int, int>>& Graph, vector<vector<int>>& AdjacencyMatrix, int n, set<int>& IDCsGraph)
		{
			auto it = IDCsGraph.begin();
			for (int i = 1; i < n + 1; ++i, ++it)
			{
				AdjacencyMatrix[0][i] = *it;
			}
			it = IDCsGraph.begin();
			for (int i = 0; i < n; ++i, ++it)
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

			//заполнение матрицы смежности 
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
		}

		void CreatingTopologicalSortingQueue(int n, queue<int>& SortingResult, vector<vector<int>>& AdjacencyMatrix)
		{
			int k = 0;
			while (k < n + 1 && SortingResult.size() != n)
			{
				for (int i = 1; i < n + 1; ++i)
				{
					if (SummCollumn(n, i, AdjacencyMatrix) == -1)
					{
						SortingResult.push(AdjacencyMatrix[0][i]);
						AdjacencyMatrix[n + 1][i] = 0;
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
				cout << "Топологическая сортировка для цикличного графа невозможна!" << endl;
			}
		}

	bool TopologicalSorting(unordered_map<int, pair <int, int>>& Graph)
	{
		//выборка ID КС, между которыми есть хотя бы одна связь
		set<int> IDCsGraph;
		if (SelectionOfTheCSGraphID(Graph, IDCsGraph) == false)
			return false;
		int n = (int)IDCsGraph.size();
		//создание заготовки для матрицы смежности
		vector<vector<int>> AdjacencyMatrix = { vector<int>(n + 1,0) };
		CreatingAndFillingInTheAdjacencyMatrix(Graph, AdjacencyMatrix, n, IDCsGraph);
		OutputAdjacencyMatrix(AdjacencyMatrix);
		AdjacencyMatrix.push_back(vector<int>(n + 1, -1));
		//создание вектора топологической сортировки
		queue<int> SortingResult;
		CreatingTopologicalSortingQueue(n, SortingResult, AdjacencyMatrix);
		//вывод стека в консоль
		cout << endl;
		while (SortingResult.size() > 0)
		{
			cout << SortingResult.front() << " ";
			SortingResult.pop();
		}
		cout << endl;
	}

	int GraphManagementConsole(unordered_map<int, Pipe>& MapP, unordered_map<int, Cs>& MapCs, forward_list<int>& FreePipes, unordered_map<int, pair <int, int>>& Graph)
	{
		int item = IntInput(0, 4);

		switch (item)
		{
		case 1:
		{
			if (!CheckingFulfillmentConditionsToGraph(MapCs))
				return false;
		
			AddingAnEdgeToGraph(MapP, MapCs, FreePipes, Graph);

			PauseAndClearing();
			return true;
		}
		case 2:
			{//прописать проверку на наличие элементов в графе
			cout << "Введите 0, для удаления труб из графа" << endl
				<< "Или 1, для удаления вершин из графа" << endl;

			int item1 = IntInput(0, 1);
			switch (item1)
			{
				
			case 0:
			{
				cout << "Введите через Enter ID труб, которые нужно удалить." << endl
					<< "Для завершения ввода введите 0" << endl;
				int ID;
				unordered_set<int> SetP;
				
				InputAndCheckingAvailabilityID(Graph, ID,MapP);
				while (ID != 0)
				{
					SetP.emplace(ID);
						InputAndCheckingAvailabilityID(Graph, ID, MapP);
				}
				cout << endl;

				for (const auto elem : SetP)
				{
					MapCs.at(Graph.at(elem).first).StopWorkshop();
					MapCs.at(Graph.at(elem).second).StopWorkshop();
					Graph.erase(elem);
					FreePipes.push_front(elem);
				}

			}
			case 1:
			{
				cout << "Введите через Enter ID КС, которые нужно удалить." << endl
					<< "Для завершения ввода введите 0" << endl;
				int ID;
				unordered_set<int> SetP;

				set<int> IDCsGraph;
				if (SelectionOfTheCSGraphID(Graph, IDCsGraph) == false)
					return false;
				int n = (int)IDCsGraph.size();
				//создание заготовки для матрицы смежности
				vector<vector<int>> AdjacencyMatrix = { vector<int>(n + 1,0) };
				CreatingAndFillingInTheAdjacencyMatrix(Graph, AdjacencyMatrix, n, IDCsGraph);

				InputAndCheckingAvailabilityID(IDCsGraph, ID, MapCs);
				while (ID != 0)
				{
					SetP.emplace(ID);
					InputAndCheckingAvailabilityID(IDCsGraph, ID, MapCs);
				}
				cout << endl;

				for 

				for (const auto elem : SetP)
				{
					MapCs.at(Graph.at(elem).first).StopWorkshop();
					MapCs.at(Graph.at(elem).second).StopWorkshop();
					Graph.erase(elem);
					FreePipes.push_front(elem);
				}
			}
						
			}

		}
			//DeletingGraphObjects(Graph);

			PauseAndClearing();
			return true;
		case 3:
		{
			TopologicalSorting(Graph);
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

void WorkingWithGraph(unordered_map<int, Pipe>& MapP, unordered_map<int, Cs>& MapCs, forward_list<int>& FreePipes, unordered_map<int, pair <int, int>>& Graph)
{
	do {
		cout << endl;
		cout << " Меню работы с графом газотранспортной сети: " << endl
			<< "1. Соединить КС" << endl
			<< "2. Удалить объект" << endl
			<< "3. Провести топологическую сортировку" << endl
			<< "4. Вывести информацию по соеднённым КС"<<endl
			<< "0. Выход в Главное меню" << endl << endl;
	} while (GraphManagementConsole(MapP, MapCs, FreePipes, Graph) != 0);
}