#pragma once
#include "OutputAndMmodification.h"


void ReadingFromFile(unordered_map<int, Pipe>& MapP, unordered_map<int, Cs>& MapCs, forward_list<int>& FreePipes, unordered_map<int, pair <int, int>>& Graph);
void OutputInFile(unordered_map<int, Pipe>& MapP, unordered_map<int, Cs>& MapCs, forward_list<int>& FreePipes, unordered_map<int, pair <int, int>>& Graph);