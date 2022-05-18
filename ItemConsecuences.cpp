#include "ItemConsecuences.h"

ItemConsecuences::ItemConsecuences(Exits* exit, bool reversible)
{
	Objective = exit;
	typeChange = Type::EXITS;
	this->reversible = reversible;
	spent = false;
}

ItemConsecuences::ItemConsecuences(Item* item,bool reversible, const char* pickableDescription)
{
	Objective = item;
	typeChange = Type::ITEM;
	this->pickableDescription = pickableDescription;
	this->reversible = reversible;
	spent = false;
}

ItemConsecuences::ItemConsecuences(Entity* entity, bool reversible)
{
	Objective = entity;
	typeChange = Type::ENTITY;
	this->reversible = reversible;
	spent = false;
}

ItemConsecuences::ItemConsecuences(Entity* entity, bool reversible, string name, string description)
{
	Objective = entity;
	this->name = name;
	this->description = description;
	typeChange = Type::ENTITY;
	this->reversible = reversible;
	spent = false;
}

ItemConsecuences::ItemConsecuences(Entity* entity, Entity* parent, bool reversible)
{
	Objective = entity;
	this->parent = parent;
	typeChange = Type::ENTITY;
	this->reversible = reversible;
	spent = false;
}

ItemConsecuences::ItemConsecuences(Creature* creature, Stats stattype, int value, bool reversible)
{
	Objective = creature;
	this->stattype = stattype;
	this->valuestat = value;
	typeChange = Type::CREATURE;
	this->reversible = reversible;
	spent = false;
}

ItemConsecuences::~ItemConsecuences()
{
}

void ItemConsecuences::Action()
{
	switch (typeChange)
	{
	case Type::ENTITY:
		EntityAction();
		break;
	case Type::ITEM:
		ItemAction();
		break;
	case Type::EXITS:
		ExitAction();
		break;
	case Type::CREATURE:
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
