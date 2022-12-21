#include "Creature.h"


void CreatingPipe(unordered_map<int, Pipe>& MapP, forward_list<int>& FreePipes)
{
	CreatingObject(MapP);
	int id = Pipe::GetID();
	FreePipes.push_front(id);
}