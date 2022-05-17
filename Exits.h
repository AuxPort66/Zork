#ifndef __Exits__
#define __Exits__
#include "Entity.h"
#include "Room.h"
class Exits :
    public Entity
{
public:
    Exits(const char* name, const char* description, Room* origin, Room* destination, const char* goAction);
    Room* GetDestination(Room* actualroom);
    string GetGoActionDescription();

    bool lock;

private:
    Room* destination;
    string goAction;
};
#endif
