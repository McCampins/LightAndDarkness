#include <iostream>

#include "Player.h"
#include "Globals.h"
#include "Exit.h"
#include "Room.h"

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
	} else
	{
		parent->Look();
	}
}

void Player::Go(const std::vector<std::string>& args)
{
	Exit* exit = GetRoom()->GetExit(args[1]);

	if (exit == nullptr)
	{
		cout << "There is no exit to the " << args[1] << "." << endl;
		return;
	}

	if (exit->locked)
	{
		cout << "This exit is locked." << endl;
		return;
	}

	cout << "You go through a " << exit->GetNameFrom((Room*)parent) << "." << endl;
	ChangeParentTo(exit->GetDestinationFrom((Room*)parent));
	parent->Look();
}
