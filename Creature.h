#ifndef __Creature__
#define __Creature__
#include "Entity.h"

enum Stats {
    HP, PERCEPTION, STRENGHT, DEFENSE
};

class Creature :
    public Entity
{
public:

    

    Creature(const char* name, const char* description, Entity* parent);

    void ChangeStat(Stats type, int value);

    int GetStat(Stats type);

    int hp;
    int perception;
    int strenght;
    int defense;

};

#endif //__Creature__

