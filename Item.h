#ifndef __Item__
#define __Item__
#include "Entity.h"
class Item :
    public Entity
{
public:
    Item(const char* name, const char* description, Entity* parent, const char* pickupAction, const char* useAction, bool pickable, bool dropable);
    string GetUseActionDescription();
    string GetPickupActionDescription();

    bool pickable;
    bool dropable;

private:
    string pickupDescription;
    string useDescription;
    
};

#endif //__Item__