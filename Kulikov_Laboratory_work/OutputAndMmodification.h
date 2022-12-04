#pragma once
#include "Pipe.h"
#include "Checking.h"
#include "Cs.h"
#include <unordered_set>
#include "OperatorOverloads.h"

void InformationOutput(const unordered_map<int, Pipe>& MapP, unordered_map<int, Cs>& MapCs);
void ChangingObjects(unordered_map<int, Pipe>& MapP, unordered_map<int, Cs>& MapCs);

string EnteringFileName();