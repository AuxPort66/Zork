#include "Entity.h"

Entity::Entity(const char* name, const char* description, Entity* parent) {

	this->name = name;
	this->description = description;
	this->accesibleContent = true;

	if (parent != NULL) {
		parent->AddChild(this);
		this->parent = parent;
	}
}

void Entity::AddChild(Entity* child) {
	content.push_back(child);
	child->parent = this;
}

void Entity::RemoveChild(Entity* child) {
	content.remove(child);	
}

Entity* Entity::CheckifContains(string name) {

	if (accesibleContent) {
		for (auto const& child : content) {
			if (child->name == name) return child;
			else if (child->Getcontent().size() > 0) {
				Entity* entityfound = child->CheckifContains(name);
				if (entityfound != NULL) return entityfound;
			}
		}
	}

	return NULL;
}

Entity* Entity::GetParent() {
	return parent;
}

void Entity::SetParent(Entity* parent)
{
	this->parent = parent;
}

list<Entity*> Entity::Getcontent() {
	return content;
}

string Entity::GetDescription() {
	return description;
}

void Entity::SetDescription(string description)
{
	this->description = description;
}

string Entity::GetName() {
	return name;
}