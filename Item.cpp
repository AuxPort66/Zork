#include "Item.h"
#include "ItemActions.h"

Item::Item(const char* name, const char* description, Entity* parent, const char* pickupAction, const char* useAction) : Entity(name, description, parent)
{
	type = ITEM;

	this->pickupDescription = pickupAction;
	this->useDescription = useAction;
	this->pickable = true;
	this->dropable = true;
}

string Item::GetUseActionDescription()
{
	return useDescription;
}


string Item::GetPickupActionDescription()
{
	return pickupDescription;
}

void Item::AddAction(ItemActions* action)
{
	actions.push_back(action);
}

void Item::UseItem()
{
	for (ItemActions* action : actions) {
		action->Action();
		if (!action->reversible) {
			actions.remove(action);
			delete action;
		}
	}
}



