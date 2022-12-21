#pragma once
#include <unordered_set>
#include "OperatorOverloads.h"

void InformationOutput(const unordered_map<int, Pipe>& MapP, unordered_map<int, Cs>& MapCs);
void ChangingObjects(unordered_map<int, Pipe>& MapP, unordered_map<int, Cs>& MapCs, unordered_map<int, pair <int, int>>& Graph, forward_list<int>& FreePipes);

string EnteringFileName();