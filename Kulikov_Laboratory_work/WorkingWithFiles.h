#pragma once
#include "OutputAndMmodification.h"


void ReadingFromFile(unordered_map<int, Pipe>& MapP, unordered_map<int, Cs>& MapCs, forward_list<int>& D500, forward_list<int>& D700, forward_list<int>& D1400, unordered_map<int, pair <int, int>>& Graph);
void OutputInFile(unordered_map<int, Pipe>& MapP, unordered_map<int, Cs>& MapCs, forward_list<int>& D500, forward_list<int>& D700, forward_list<int>& D1400, unordered_map<int, pair <int, int>>& Graph);