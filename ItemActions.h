#ifndef __ItemActions__
#define __ItemActions__
#include "Entity.h"
#include "Exits.h"
#include "Item.h"
#include "Creature.h"

class ItemActions
{
public:
	ItemActions(Exits* exit, bool reversible); //Open a Exit
	ItemActions(Item* item, bool reversible); //Pickable item
	ItemActions(Entity* entity, bool reversible); //Change accesibility content


	ItemActions(Entity* entity, string name, string description, bool reversible); //Change description and name
	ItemActions(Entity* entity, Entity* parent, bool reversible); //Change Parent
	ItemActions(Creature* creature, Stats stattype, int value, bool reversible); //Add the value to the stat of the creature

	~ItemActions();

	void Action();

	void EntityAction();

	void ItemAction();

	void ExitAction();

	void CreatureAction();

	bool reversible;

private:
	Entity* Objective;
	Type change;
	string name = "";
	string description = "";
	Entity* parent = NULL;
	Stats stattype = HP;
	int valuestat = NULL;
};

#endif // __ItemActions__