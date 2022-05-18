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

void Item::SetPickupActionDescription(string pickupDescription)
{
	this->pickupDescription = pickupDescription;
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
			if ((action->positionofusedOn == NULL || (action->positionofusedOn == usedOn->GetParent()))) {
				for (ItemConsecuences* consecuence : action->consecuences) {
					if (!consecuence->marked) {
						consecuence->Action();
						used = true;
					}
					if (!consecuence->reversible) {
						consecuence->marked = true;
					}
				}
				if (used) {
					cout << ">> " << action->useDescription << endl;
				}
			}
			else {
				cout << ">> Not here!" << endl;
				used = true;
			}
		}
	}
	if (!used) cout << ">> That do nothing" << endl;
	else if (lostOnUse) {
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

list<Action*> Item::GetActions()
{
	return actions;
}



