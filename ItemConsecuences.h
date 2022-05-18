#ifndef __ItemConsecuences__
#define __ItemConsecuences__
#include "Entity.h"
#include "Exits.h"
#include "Item.h"
#include "Creature.h"

class ItemConsecuences
{
public:
	ItemConsecuences(Exits* exit, bool reversible); //Open a Exit
	ItemConsecuences(Item* item, bool reversible, const char* pickableDescription); //Pickable Item
	ItemConsecuences(Entity* entity, bool reversible); //Change accesibility content


	ItemConsecuences(Entity* entity, bool reversible, string name, string description); //Change description and name
	ItemConsecuences(Entity* entity, Entity* parent, bool reversible); //Change Parent
	ItemConsecuences(Creature* creature, Stats stattype, int value, bool reversible); //Add the value to the stat of the creature

	~ItemConsecuences();

	void Action();
	void EntityAction();
	void ItemAction();
	void ExitAction();
	void CreatureAction();

	bool reversible;
	bool spent;
private:
	Entity* Objective;
	Type typeChange;
	string name = "";
	string description = "";
	string pickableDescription = "";
	Entity* parent = NULL;
	Stats stattype = Stats::HP;
	int valuestat = NULL;

};

#endif // __ItemConsecuences__