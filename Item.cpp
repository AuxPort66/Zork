#include "Item.h"

Item::Item(const char* name, const char* description, Entity* parent, const char* pickupAction, const char* useAction, bool pickable, bool dropable) : Entity(name, description, parent)
{
	type = ITEM;

	this->pickupDescription = pickupAction;
	this->useDescription = useAction;
	this->pickable = pickable;
	this->dropable = dropable;
}

string Item::GetUseActionDescription()
{
	return useDescription;
}


string Item::GetPickupActionDescription()
{
	return pickupDescription;
}


