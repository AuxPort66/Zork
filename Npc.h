#ifndef __Npc__
#define __Npc__
#include "Creature.h"

class ItemConsecuences;

struct Interaction {
    bool repetible;
    bool spent;
    Entity* activewithItem;
    list<ItemConsecuences*> consecuences;
    list <string> dialogue;

    Interaction(Entity* activewithItem) {
        this->activewithItem = activewithItem;
        repetible = true;
        spent = false;
    }

    void AddDialogue(const char* dialogue) {
        this->dialogue.push_back(dialogue);
    }

    void Addconsecuence(ItemConsecuences* consecuence) {
        consecuences.push_back(consecuence);
    }
};

class Npc :
    public Creature
{
public:
    Npc(const char* name, const char* description, Entity* parent);
    ~Npc();
    void AddInteraction(Interaction* interaction);
    void ActiveInteraction(Entity* usedItem);

private:
    list<Interaction*> interactions;
};

#endif // __Npc__