#include "Exits.h"

Exits::Exits(const char* name, Room* origin, Room* destination, const char* description) : Entity(name, description, (Entity*)origin) {
	
	type = Type::EXITS;
	
	this->lock = false;
	this->destination = destination;
	destination->AddChild(this);
	this->parent = origin;
	string goactionDescription = "Go through " + this->name;
	this->goActionDescription = goactionDescription;
}

Exits::~Exits()
{
}

Room* Exits::GetDestination(Room* actualroom) {
	if (actualroom == parent) return destination;
	else if(actualroom == destination) return (Room*)parent;

	return NULL;
}

string Exits::GetGoActionDescription() {
	return goActionDescription;
}

void Exits::SetGoActionDescription(string goActionDescription)
{
	this->goActionDescription = goActionDescription;
}
