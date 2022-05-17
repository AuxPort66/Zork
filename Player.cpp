#include "Player.h"

Player::Player(const char* name, const char* description, Entity* parent) : Creature(name,description,parent)
{
	type = PLAYER;
}