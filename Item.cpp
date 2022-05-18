#include "Item.h"
#include "ItemConsecuences.h"
#include <iostream>

Item::Item(const char* name, Entity* parent, const char* description) : Entity(name, description, parent)
{
	type = Type::ITEM;

	this->pickupDescription = "";
	this->pickable = true;
	this->dropable = true;
	this->lostOnUse = false;
	this->usedWhenPick = false;
	this->noCapacity = true;
}

Item::~Item()
{
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
					if (!consecuence->spent) {
						consecuence->Action();
						used = true;
					}
					if (!consecuence->reversible) {
						consecuence->spent = true;
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



