#ifndef __Player__
#define __Player__
#include "Creature.h"
class Player :
    public Creature
{
public:
    Player(const char* name, Entity* parent, const char* description);
    ~Player();

    bool tp;
};

#endif //__Player__
