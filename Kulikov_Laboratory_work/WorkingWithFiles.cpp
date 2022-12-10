#include "WorkingWithFiles.h"


//Вывод в файл
//Вывод объекта и его ID в файл
template<typename T>
void OutputInFileObject(ofstream& fout, unordered_map<int, T>& Obj)
{
	for (const auto& elem : Obj)
	{
		fout << elem.first << endl;
		OutputObjectsFile(fout, elem.second);
		fout << endl;
	}
}
//Вывод в файл 
void OutputInFile(unordered_map<int, Pipe>& MapP, unordered_map<int, Cs>& MapCs, forward_list<int>& D500, forward_list<int>& D700, forward_list<int>& D1400, unordered_map<int, pair <int, int>>& Graph)
{
	cout << "5.Сохранение в файл." << endl;
	string way = EnteringFileName();

	ofstream fout;
	fout.exceptions(ofstream::badbit | ofstream::failbit);
	//https://www.youtube.com/watch?v=jCW2wRoRi0U

	try
	{
		fout.open(way);

		fout << MapP.size() << endl << MapCs.size() << endl << endl;
		OutputInFileObject(fout, MapP);
		OutputInFileObject(fout, MapCs);

		fout << Graph.size()<<endl;
		fout << Graph<<endl;

		fout << D500 << endl;
		fout << -1<<endl;

		fout << D700 << endl;
		fout << -1 << endl;

		fout << D1400 << endl;
		fout << -1 << endl;

		fout.close();
		cout << "Данные сохранены";
	}
	catch (const  ofstream::failure& ex)
	{
		cout << ex.what() << endl << ex.code() << endl << "Ошибка при открытии/создании файла" << endl;
	}

}

//Считывание из файла

	//Считывание объектов из файла
template<typename T>
void ReadingPipesFromFile(ifstream& fin, unordered_map<int, T>& Obj, int& Number)
{
	int ObjID = 0;
	T obj;
	while (Number != 0)
	{
		fin >> ObjID;
		fin >> obj;

		Obj.emplace(ObjID, obj);

		--Number;
	}
	T::IDreplacement(Obj);
}

//Считывание из файла 
void ReadingFromFile(unordered_map<int, Pipe>& MapP, unordered_map<int, Cs>& MapCs, forward_list<int>& D500, forward_list<int>& D700, forward_list<int>& D1400, unordered_map<int, pair <int, int>>& Graph)
{
	cout << "6.Загрузка данных из файла." << endl
		<< "Данное действие приведёт к перезаписи введёных данных (если они есть). Убедитесь, что они вам не нужны." << endl
		<< "Введите 1, чтобы продолжить, либо 0 для отмены загрузки." << endl;
	if (EnteringCheckingBool())
	{
		ifstream fin;
		fin.exceptions(ifstream::failbit);
		int NumberPipes = 0;
		int NumberCs = 0;
		string way = EnteringFileName();

		try
		{
			fin.open(way, ios::in);

			fin >> NumberPipes;
			fin >> NumberCs;

			if (NumberPipes != 0 || NumberCs != 0)
			{
				ReadingPipesFromFile(fin, MapP, NumberPipes);
				ReadingPipesFromFile(fin, MapCs, NumberCs);
			}

			fin >> Graph;

			fin >> D500;
			fin >> D700;
			fin >> D1400;
		}
		catch (const  ifstream::failure& ex)
		{
			cout << ex.what() << endl << ex.code() << endl << "Ошибка при открытии файла" << endl;
		}
	}
}
