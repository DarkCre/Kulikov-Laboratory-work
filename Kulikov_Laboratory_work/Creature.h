#pragma once
#include "Checking.h"
#include <forward_list>

void CreatingPipe(unordered_map<int, Pipe>& MapP, forward_list<int>& FreePipes);

//Создание нового элемента
template<typename T>
void CreatingObject(unordered_map<int, T>& Obj)
{
	T obj;
	cin >> obj;
	Obj.emplace(obj.GetID(), obj);
}
