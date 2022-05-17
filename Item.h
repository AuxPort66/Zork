#ifndef __Item__
#define __Item__
#include "Entity.h"

class ItemActions;

class Item :
    public Entity
{
public:
    Item(const char* name, const char* description, Entity* parent, const char* pickupAction, const char* useAction);
    string GetUseActionDescription();
    string GetPickupActionDescription();

    void AddAction(ItemActions* action);

    void UseItem();

    bool pickable;
    bool dropable;

private:
    string pickupDescription;
    string useDescription;
    list<ItemActions*> actions;
};

#endif //__Item__