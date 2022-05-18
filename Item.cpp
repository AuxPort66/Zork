#include "Item.h"
#include "ItemConsecuences.h"
#include <iostream>

Item::Item(const char* name, const char* description, Entity* parent, const char* pickupAction) : Entity(name, description, parent)
{
	type = ITEM;

	this->pickupDescription = pickupAction;
	this->pickable = true;
	this->dropable = true;
	this->lostOnUse = false;
}


string Item::GetPickupActionDescription()
{
	return pickupDescription;
}

void Item::AddAction(Action* action)
{
	actions.push_back(action);
}


void Item::UseItem(Entity* usedOn)
{
	bool used = false;
	for (Action* action : actions) {
		if (action->usedOn == usedOn) {
			for (ItemConsecuences* consecuence : action->consecuences) {
				consecuence->Action();
				if (!consecuence->reversible) {
					action->consecuences.remove(consecuence);
					delete consecuence;
					if (action->consecuences.size() == 0) {
						actions.remove(action);
						delete action;
					}
				}
			}
			cout << action->useDescription << endl;
			used = true;
		}
	}
	if (used && lostOnUse) {
		this->parent->RemoveChild(this);
		for (Action* action : actions) {
			for (ItemConsecuences* consecuence : action->consecuences) {
				delete consecuence;
			}
			delete action;
		}
		delete this;
	}
}



