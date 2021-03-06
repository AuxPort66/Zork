#include "Npc.h"
#include "ItemConsecuences.h"
#include <iostream>

Npc::Npc(const char* name, const char* description, Entity* parent) : Creature(name, description, parent)
{
	type = Type::NPC;
}

Npc::~Npc()
{
}

void Npc::AddInteraction(Interaction* interaction)
{
	interactions.push_back(interaction);
}

void Npc::ActiveInteraction(Entity* usedItem)
{
	bool used = false;
	for (Interaction* interaction : interactions) {
		if (interaction->activewithItem == usedItem) {
			for (string dialogue : interaction->dialogue) {
				cout << ">> " << dialogue << endl;
			}

			for (ItemConsecuences* consecuence : interaction->consecuences) {
				if (!consecuence->spent)consecuence->Action();
				if (!consecuence->reversible) {
					consecuence->spent = true;
				}
			}
			used = true;
		}
		if (used) {
			if (interaction->activewithItem != NULL) {
				Item* itemUsed = (Item*)usedItem;
				if (itemUsed->lostOnUse) {
					itemUsed->GetParent()->RemoveChild(usedItem);
					for (Action* action : itemUsed->GetActions()) {
						for (ItemConsecuences* consecuence : action->consecuences) {
							delete consecuence;
						}
						delete action;
					}
					delete itemUsed;
				}
			}
			if (!interaction->repetible) {
				interactions.remove(interaction);
				delete interaction;
			}
			break;
		}
	}
}
