#include "ItemConsecuences.h"

ItemConsecuences::ItemConsecuences(Exits* exit, bool reversible)
{
	Objective = exit;
	change = EXITS;
	this->reversible = reversible;
	marked = false;
}

ItemConsecuences::ItemConsecuences(Item* item,string pickableDescription ,bool reversible)
{
	Objective = item;
	change = ITEM;
	this->pickableDescription = pickableDescription;
	this->reversible = reversible;
	marked = false;
}

ItemConsecuences::ItemConsecuences(Entity* entity, bool reversible)
{
	Objective = entity;
	change = ENTITY;
	this->reversible = reversible;
	marked = false;
}

ItemConsecuences::ItemConsecuences(Entity* entity, string name, string description, bool reversible)
{
	Objective = entity;
	this->name = name;
	this->description = description;
	change = ENTITY;
	this->reversible = reversible;
	marked = false;
}

ItemConsecuences::ItemConsecuences(Entity* entity, Entity* parent, bool reversible)
{
	Objective = entity;
	this->parent = parent;
	change = ENTITY;
	this->reversible = reversible;
	marked = false;
}

ItemConsecuences::ItemConsecuences(Creature* creature, Stats stattype, int value, bool reversible)
{
	Objective = creature;
	this->stattype = stattype;
	this->valuestat = value;
	change = CREATURE;
	this->reversible = reversible;
	marked = false;
}

ItemConsecuences::~ItemConsecuences()
{
}

void ItemConsecuences::Action()
{
	switch (change)
	{
	case ENTITY:
		EntityAction();
		break;
	case ITEM: 
		ItemAction();
		break;
	case EXITS:
		ExitAction();
		break;
	case CREATURE:
		CreatureAction();
		break;
	}
}

void ItemConsecuences::EntityAction() {
	if (parent != NULL) {
		Entity* oldparent = Objective->GetParent();
		oldparent->RemoveChild(Objective);
		parent->AddChild(Objective);
		if (reversible) parent = oldparent;
	}
	else if (name != "" || description != "") {
		if (name != "") {
			string oldname = Objective->name;
			Objective->name = name;
			if (reversible) name = oldname;
		}
		if (description != "") {
			string olddescription = Objective->GetDescription();
			Objective->SetDescription(description);
			if (reversible) description = description;
		}
	}
	else
	{
		Objective->accesibleContent = !Objective->accesibleContent;
	}
}

void ItemConsecuences::ItemAction() {
	Item* item = (Item*)Objective;
	string oldDescription = item->GetPickupActionDescription();
	item->reachable = !item->reachable;
	if (pickableDescription != "") {
		item->SetPickupActionDescription(pickableDescription);
		pickableDescription = oldDescription;
	}

}

void ItemConsecuences::ExitAction() {
	Exits* exit = (Exits*)Objective;
	exit->lock = !exit->lock;
}

void ItemConsecuences::CreatureAction() {
	Creature* creature = (Creature*)Objective;
	creature->ChangeStat(stattype, valuestat);
	if (reversible) valuestat = -valuestat;
}
