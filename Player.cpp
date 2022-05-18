#include "Player.h"

Player::Player(const char* name, Entity* parent, const char* description) : Creature(name,description,parent)
{
	type = Type::PLAYER;
	this->tp = false;
}

Player::~Player()
{
}