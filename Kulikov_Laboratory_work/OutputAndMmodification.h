#pragma once
#include <unordered_set>
#include "OperatorOverloads.h"

void InformationOutput(const unordered_map<int, Pipe>& MapP, unordered_map<int, Cs>& MapCs);
void ChangingObjects(unordered_map<int, Pipe>& MapP, unordered_map<int, Cs>& MapCs);

string EnteringFileName();