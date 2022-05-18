#ifndef __Entity__
#define __Entity__
#include <list>
#include <vector>
#include <string>
using namespace std;

enum Type {
	ENTITY, ROOM, ITEM, EXITS, CREATURE, PLAYER, NPC
};

class Entity
{
public:
	Entity(const char* name, const char* description, Entity* parent);
	void AddChild(Entity* child);

	void RemoveChild(Entity* child);

	Entity* CheckifContains(string name);

	Entity* GetParent();
	void SetParent(Entity* parent);

	list<Entity*> Getcontent();

	string GetDescription();
	void SetDescription(string description);

	string GetName();



	string name;
	Type type;
	bool accesibleContent;
	bool reachable;

protected:

	vector<string> synonims;
	vector<string> adjectives;
	string description;

	Entity* parent;
	list<Entity*> content;

};

#endif //__Entity__
