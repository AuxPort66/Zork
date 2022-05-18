#ifndef __Item__
#define __Item__
#include "Entity.h"

class ItemConsecuences;

struct Action {
    Entity* usedOn;
    list<ItemConsecuences*> consecuences;
    string useDescription;

    Action(Entity* usedOn,const char* useDescription) {
        this->usedOn = usedOn;
        this->useDescription = useDescription;
    }

    void Addconsecuence(ItemConsecuences* consecuence) {
        consecuences.push_back(consecuence);
    }
};

class Item :
    public Entity
{
public:
    Item(const char* name, const char* description, Entity* parent, const char* pickupAction);
    string GetPickupActionDescription();

    void AddAction(Action* action);

    void UseItem(Entity* usedOn);

    bool pickable;
    bool dropable;
    bool lostOnUse;

private:
    string pickupDescription;
    list<Action*> actions;
};

#endif //__Item__