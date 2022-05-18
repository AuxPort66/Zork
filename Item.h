#ifndef __Item__
#define __Item__
#include "Entity.h"

class ItemConsecuences;

struct Action {
    Entity* usedOn;
    Entity* positionofusedOn;
    list<ItemConsecuences*> consecuences;
    string useDescription;

    Action(Entity* usedOn,const char* useDescription) {
        this->usedOn = usedOn;
        this->useDescription = useDescription;
        this->positionofusedOn = NULL;
    }

    void Addconsecuence(ItemConsecuences* consecuence) {
        consecuences.push_back(consecuence);
    }
};

class Item :
    public Entity
{
public:
    Item(const char* name, Entity* parent, const char* description);
    ~Item();
    string GetPickupActionDescription();
    void SetPickupActionDescription(string pickupDescription);

    void AddAction(Action* action);
    void UseItem(Entity* usedOn);
    list<Action*> GetActions();

    bool pickable;
    bool dropable;
    bool lostOnUse;
    bool usedWhenPick;

private:
    string pickupDescription;
    list<Action*> actions;
};

#endif //__Item__