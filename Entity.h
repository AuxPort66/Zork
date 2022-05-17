#ifndef __Entity__
#define __Entity__
#include <list>
#include <vector>
#include <string>
using namespace std;

enum Type {
	ENTITY, ROOM, ITEM, EXIT, CREATURE, PLAYER
};

class Entity
{
public:
	Entity(const char* name, const char* description, Entity* parent);
	void AddChild(Entity* child);

	void RemoveChild(Entity* child);

	Entity* CheckifContains(string name);

	string GetDescription();

	string GetName();


	string name;
	Type type;

protected:

	vector<string> synonims;
	vector<string> adjectives;
	string description;

	Entity* parent;
	list<Entity*> content;

};

#endif //__Entity__
