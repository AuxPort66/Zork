#ifndef __Entity__
#define __Entity__
#include <list>
#include <vector>
#include <string>
using namespace std;

enum class Type {
	ENTITY, ROOM, ITEM, EXITS, CREATURE, PLAYER, NPC
};

class Entity
{
public:
	Entity(const char* name, const char* description, Entity* parent);
	~Entity();
	void AddChild(Entity* child);
	void RemoveChild(Entity* child);

	Entity* CheckifContains(string name);

	Entity* GetParent();
	void SetParent(Entity* parent);

	string GetDescription();
	void SetDescription(string description);

	list<Entity*> Getcontent();

	string GetName();

	string name;
	Type type;
	bool accesibleContent;
	bool reachable;

	bool dropped;
	int havedropped;
	bool alwaysReachable;

protected:
	string description;
	Entity* parent;
	list<Entity*> content;
};

#endif //__Entity__
