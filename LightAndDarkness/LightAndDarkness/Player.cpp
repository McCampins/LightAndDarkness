#include <iostream>

#include "Player.h"
#include "Globals.h"

using namespace std;

Player::Player(const char* name, const char* description, Room* room, const char* state) :
	Creature(name, description, room, state)
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
		for (vector<Entity*>::const_iterator it = parent->container.begin(); it != parent->container.cend(); ++it)
		{
			if (Same((*it)->name, args[1]))
			{
				(*it)->Look();
				return;
			}
		}

		if (Same(args[1], "myself"))
		{
			cout << name << endl;
			cout << description << endl;
			return;
		}

		cout << "Can't find this entity." << endl;
	} 
	else
	{
		parent->Look();
	}
}
