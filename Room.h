#ifndef __Room__
#define __Room__
#include "Entity.h"
class Room : public Entity
{
public:
    Room(const char* name, Entity* parent, const char* description);
    ~Room();

};

#endif //__Room__

