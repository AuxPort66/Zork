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

Entity* Entity::CheckifContains(string name) {
	for (int i = 0; i < content.size(); i++) {
		if (content[i]->name == name) {
			return content[i];
		}
	}
	return NULL;
}

string Entity::GetDescription() {
	return description;
}

string Entity::GetName() {
	return name;
}