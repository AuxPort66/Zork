#ifndef __World__
#define __World__
#include <vector>
#include <string>
#include <iostream>
#include "Entity.h"
#include "Room.h"
#include "Exits.h"
#include "Item.h"
#include "Player.h"
#include "ItemConsecuences.h"

class World
{
public:
	void Start();
	void ParseAction(vector<string> args);
	void Use(string nameObjectUsed, string nameObjectUsedOn);
	void Examine(string name);
	void Go(string destino);
	void Pick(string name);
	void Drop(string dropped, string container);
	void Inventory(Entity* inventory);
	void PrintRoom(Room* room);
	void PrintStats(Creature* creature);
private:
	vector<Entity> map;
	Room* actualRoom;
	Player* player;

};

#endif //__World__

