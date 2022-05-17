#ifndef __World__
#define __World__
#include <vector>
#include <string>
#include <iostream>
#include "Entity.h"
#include "Room.h"
#include "Exits.h"
#include "Item.h"

class World
{
public:
	void Start();
	void ParseAction(vector<string> args);
	void Look(string name);
	void Go(string destino);
	void Pick(string name);
	void Drop(string name);
	Item* isInInventory(string name);
	void Inventory();
	void PrintRoom(Room* room);
private:
	vector<Entity> map;
	Room* actualRoom;

};

#endif //__World__

