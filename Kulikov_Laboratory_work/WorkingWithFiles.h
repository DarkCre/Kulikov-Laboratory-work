#pragma once

#include "Cs.h"
#include "Pipe.h"
#include "OutputAndMmodification.h"


void ReadingFromFile(unordered_map<int, Pipe>& MapP, unordered_map<int, Cs>& MapCs);
void OutputInFile(unordered_map<int, Pipe>& MapP, unordered_map<int, Cs>& MapCs);