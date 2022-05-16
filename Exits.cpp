#include "Exits.h"

Exits::Exits(const char* name, const char* description, Room* origin, Room* destination, const char* goAction) : Entity(name, description, (Entity*)origin) {
	
	type = EXIT;
	
	this->destination = destination;
	destination->AddChild(this);

	this->goAction = goAction;
}

Room* Exits::GetDestination(Room* actualroom) {
	if (actualroom == parent) return destination;
	else if(actualroom == destination) return (Room*)parent;

	return NULL;
}

string Exits::GetGoActionDescription() {
	return goAction;
}
