#include <iostream>

#include "Player.h"
#include "Globals.h"
#include "Exit.h"
#include "Room.h"

using namespace std;

Player::Player(const char* name, const char* description, Room* room, const char* state) :
	Creature(name, description, room, state)
{
	type = EntityType::PLAYER;
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

		if (Same(args[1], "myself") || Same(args[1], "me"))
		{
			cout << "\n" << description << endl;
			return;
		}

		cout << "\nCan't find this entity." << endl;
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
		cout << "\nThere is no exit to the " << args[1] << "." << endl;
		return;
	}

	if (exit->oneWay)
	{
		cout << "\nAs you walk through, the door locks behind you." << endl;
	}

	if (exit->locked)
	{
		cout << "\nThis exit is locked." << endl;
		return;
	}

	cout << "\nYou go through a " << exit->description << " to the " << exit->GetNameFrom((Room*)parent) << "." << endl;
	ChangeParentTo(exit->GetDestinationFrom((Room*)parent));
	parent->Look();
}
