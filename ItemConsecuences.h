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
	ItemConsecuences(Item* item, string pickableDescription, bool reversible); //Pickable Item
	ItemConsecuences(Entity* entity, bool reversible); //Change accesibility content


	ItemConsecuences(Entity* entity, string name, string description, bool reversible); //Change description and name
	ItemConsecuences(Entity* entity, Entity* parent, bool reversible); //Change Parent
	ItemConsecuences(Creature* creature, Stats stattype, int value, bool reversible); //Add the value to the stat of the creature

	~ItemConsecuences();

	void Action();

	void EntityAction();

	void ItemAction();

	void ExitAction();

	void CreatureAction();

	bool reversible;
	bool marked;
private:
	Entity* Objective;
	Type change;
	string name = "";
	string description = "";
	string pickableDescription = "";
	Entity* parent = NULL;
	Stats stattype = HP;
	int valuestat = NULL;

};

#endif // __ItemConsecuences__