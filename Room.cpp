#include "Room.h"

Room::Room(const char* name, Entity* parent, const char* description) : Entity(name, description, parent)
{
	type = Type::ROOM;
}

Room::~Room()
{
}