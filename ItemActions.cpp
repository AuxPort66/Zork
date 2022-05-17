#include "ItemActions.h"

ItemActions::ItemActions(Exits* exit, bool reversible)
{
	Objective = exit;
	change = EXITS;
	this->reversible = reversible;
}

ItemActions::ItemActions(Item* item, bool reversible)
{
	Objective = item;
	change = ITEM;
	this->reversible = reversible;
}

ItemActions::ItemActions(Entity* entity, bool reversible)
{
	Objective = entity;
	change = ENTITY;
	this->reversible = reversible;
}

ItemActions::ItemActions(Entity* entity, string name, string description, bool reversible)
{
	Objective = entity;
	this->name = name;
	this->description = description;
	change = ENTITY;
	this->reversible = reversible;
}

ItemActions::ItemActions(Entity* entity, Entity* parent, bool reversible)
{
	Objective = entity;
	this->parent = parent;
	change = ENTITY;
	this->reversible = reversible;
}

ItemActions::ItemActions(Creature* creature, Stats stattype, int value, bool reversible)
{
	Objective = creature;
	this->stattype = stattype;
	this->valuestat = value;
	change = CREATURE;
	this->reversible = reversible;
}

ItemActions::~ItemActions()
{
}

void ItemActions::Action()
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

void ItemActions::EntityAction() {
	if (parent != NULL) {
		Entity* oldparent = Objective->GetParent();
		Objective->SetParent(parent);
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

void ItemActions::ItemAction() {
	Item* item = (Item*)Objective;
	item->pickable = !item->pickable;
}

void ItemActions::ExitAction() {
	Exits* exit = (Exits*)Objective;
	exit->lock = !exit->lock;
}

void ItemActions::CreatureAction() {
	Creature* creature = (Creature*)Objective;
	creature->ChangeStat(stattype, valuestat);
	if (reversible) valuestat = -valuestat;
}
