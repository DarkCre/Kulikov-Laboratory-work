#include "Creature.h"


void CreatingPipe(unordered_map<int, Pipe>& MapP, forward_list<int>& D500, forward_list<int>& D700, forward_list<int>& D1400)
{
	CreatingObject(MapP);
	int id = Pipe::GetID();
	if (MapP.at((int)Pipe::GetID()).GetDia() == 500) { D500.push_front(id); }
	else if (MapP.at((int)Pipe::GetID()).GetDia() == 700) { D700.push_front(id); }
	else if (MapP.at((int)Pipe::GetID()).GetDia() == 1400) { D1400.push_front(id); }
}