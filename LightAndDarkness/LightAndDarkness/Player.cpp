#include <iostream>

#include "Player.h"

Player::Player(const char* name, const char* description, Room* room) :
	Creature(name, description, room)
{
	EntityType::PLAYER;
}


Player::~Player()
{
}

void Player::Look(const vector<string>& args) const
{
	if (args.size() > 1)
	{

	} 
	else
	{
		parent->Look();
	}
}
