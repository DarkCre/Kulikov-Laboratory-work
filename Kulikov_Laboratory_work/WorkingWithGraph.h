#pragma once
#include "Checking.h"
#include "OutputAndMmodification.h"
#include "Creature.h"
#include <set>
#include <queue>


void WorkingWithGraph(unordered_map<int, Pipe>& MapP, unordered_map<int, Cs>& MapCs, forward_list<int>& FreePipes, unordered_map<int, pair <int, int>>& Graph);

