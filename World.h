#ifndef __World__
#define __World__
#include <vector>
#include <string>
#include "Entity.h"
#include "Room.h"
#include "Exits.h"
#include "Item.h"
#include "Player.h"
#include "Npc.h"
#include "ItemConsecuences.h"

class World
{
public:
	void Start();
	void ParseAction(vector<string> args);
	void Use(string nameObjectUsed, string nameObjectUsedOn);
	void Give(string nameObjectgiven, string nameNpc);
	void Talk(string nameNpc);
	void Examine(string name);
	void Go(string destino);
	void Pick(string name);
	void Drop(string dropped, string container);
	void Inventory(Entity* inventory, int layer);
	void PrintRoom(Room* room);
	void PrintStats(Creature* creature);
private:
	vector<Entity*> wholeExistance;
	Room* actualRoom;
	Player* player;

};

#endif //__World__

