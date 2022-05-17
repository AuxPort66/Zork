#include "Creature.h"
Creature::Creature(const char* name, const char* description, Entity* parent) : Entity(name, description, parent)
{
	type = CREATURE;
	this->hp = 1;
	this->strenght = 1;
	this->perception = 1;
	this->defense = 1;
}

void Creature::ChangeStat(Stats type, int value)
{
	switch (type)
	{
	case HP:
		hp += value;
		break;
	case PERCEPTION:
		perception += value;
		break;
	case STRENGHT:
		strenght += value;
		break;
	case DEFENSE:
		defense += value;
		break;
	}
}

int Creature::GetStat(Stats type) {

	switch (type)
	{
	case HP:
		return hp;
	case PERCEPTION:
		return perception;
	case STRENGHT:
		return strenght;
	case DEFENSE:
		return defense;
	}
	
}

