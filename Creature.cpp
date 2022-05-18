#include "Creature.h"
Creature::Creature(const char* name, const char* description, Entity* parent) : Entity(name, description, parent)
{
	type = Type::CREATURE;
	this->hp = 1;
	this->strenght = 1;
	this->perception = 1;
	this->defense = 1;
}

Creature::~Creature()
{
}

void Creature::ChangeStat(Stats type, int value)
{
	switch (type)
	{
	case Stats::HP:
		hp += value;
		break;
	case Stats::PERCEPTION:
		perception += value;
		break;
	case Stats::STRENGHT:
		strenght += value;
		break;
	case Stats::DEFENSE:
		defense += value;
		break;
	}
}

int Creature::GetStat(Stats type) {

	switch (type)
	{
	case Stats::HP:
		return hp;
	case Stats::PERCEPTION:
		return perception;
	case Stats::STRENGHT:
		return strenght;
	case Stats::DEFENSE:
		return defense;
	}
	return NULL;
}

