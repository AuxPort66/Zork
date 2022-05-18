#ifndef __Exits__
#define __Exits__
#include "Entity.h"
#include "Room.h"
class Exits :
    public Entity
{
public:
    Exits(const char* name, Room* origin, Room* destination, const char* description);
    ~Exits();
    Room* GetDestination(Room* actualroom);
    string GetGoActionDescription();
    void SetGoActionDescription(string goActionDescription);

    bool lock;

private:
    Room* destination;
    string goActionDescription;
};
#endif
