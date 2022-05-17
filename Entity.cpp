#include "Entity.h"

Entity::Entity(const char* name, const char* description, Entity* parent = NULL) {

	this->name = name;
	this->description = description;

	if (parent != NULL) {
		parent->AddChild(this);
		this->parent = parent;
	}
}

void Entity::AddChild(Entity* child) {
	content.push_back(child);
}

void Entity::RemoveChild(Entity* child) {
	content.remove(child);	
}

Entity* Entity::CheckifContains(string name) {


	for (auto const& child : content) {
		if (child->name == name) return child;
	}

	return NULL;
}

string Entity::GetDescription() {
	return description;
}

string Entity::GetName() {
	return name;
}