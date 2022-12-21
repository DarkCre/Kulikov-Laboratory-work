#pragma once
#include "WorkingWithGraph.h"
using namespace std;



int Ford_Fulkerson(int numOfVertex, int numOfEdge, int sourceVertex, int destinationVertex, unordered_map<int, pair <int, int>>& Graph1, unordered_map<int, Pipe>& MapP);