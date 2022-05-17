#include "Room.h"

Room::Room(const char* name, const char* description, Entity* parent) : Entity(name, description, parent)
{
	type = ROOM;
}