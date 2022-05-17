#ifndef __Player__
#define __Player__
#include "Creature.h"
class Player :
    public Creature
{
public:
    Player(const char* name, const char* description, Entity* parent);

};

#endif //__Player__
