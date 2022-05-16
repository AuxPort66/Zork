#ifndef __World__
#define __World__
#include <vector>
#include <string>
#include <iostream>
#include "Entity.h"
#include "Room.h"
#include "Exits.h"

class World
{
public:
	void Start();
	void ParseAction(vector<string> args);
	void Look(string name);
	void Go(string destino);
	void PrintRoom(Room* room);
private:
	vector<Entity> map;
	Room* actualRoom;

};

#endif //__World__

