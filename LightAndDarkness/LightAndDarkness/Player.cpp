#include <iostream>
#include <string>

#include "World.h"
#include "Player.h"
#include "Globals.h"
#include "Exit.h"
#include "Room.h"
#include "Item.h"

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
	switch (args.size())
	{
	case 0:
		return; //Error, should never happen
	case 1:
		parent->Look();
		break;
	case 2:
		if (Same(args[1], "myself") || Same(args[1], "me"))
		{
			cout << "\n" << description << endl;
			return;
		}

		for (vector<Entity*>::const_iterator it = parent->container.begin(); it != parent->container.cend(); ++it)
		{
			if (Same((*it)->name, args[1]))
			{
				(*it)->Look();
				return;
			}
		}

		cout << "\nCan't find this entity." << endl;
		break;
	case 3:
		for (vector<Entity*>::const_iterator it = parent->container.begin(); it != parent->container.cend(); ++it)
		{
			if ((*it)->type == EntityType::ITEM)
			{
				if (Same((*it)->name, args[1] + " " + args[2]))
				{
					(*it)->Look();
					return;
				}
				if ((*it)->container.empty() == false)
				{
					for (vector<Entity*>::const_iterator it2 = (*it)->container.begin(); it2 != (*it)->container.cend(); ++it2)
					{
						if (Same((*it2)->name, args[1] + " " + args[2]))
						{
							(*it2)->Look();
							return;
						}
					}
				}
			}
			else
			{
				if (Same((*it)->name, args[1]))
				{
					(*it)->Look();
					return;
				}
			}
		}

		cout << "\nCan't find this entity." << endl;
		break;
	default:
		return; //Error, should never happen
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

void Player::Open(const std::vector<std::string>& args)
{
	Item* item = nullptr;
	Item* key = nullptr;

	switch (args.size())
	{
	case 2:
		item = (Item*)GetRoom()->Find(args[1], EntityType::ITEM);
		break;
	case 3:
		item = (Item*)GetRoom()->Find(args[1] + " " + args[2], EntityType::ITEM);
		break;
	case 4:
		if (Same(args[2], "with"))
		{
			item = (Item*)GetRoom()->Find(args[1], EntityType::ITEM);
			key = (Item*)GetRoom()->Find(args[3], EntityType::ITEM);
		}
		break;
	case 5:
		if (Same(args[3], "with"))
		{
			item = (Item*)GetRoom()->Find(args[1] + " " + args[2], EntityType::ITEM);
			key = (Item*)GetRoom()->Find(args[4], EntityType::ITEM);
		}
		break;
	case 6:
		if (Same(args[3], "with"))
		{
			item = (Item*)GetRoom()->Find(args[1] + " " + args[2], EntityType::ITEM);
			key = (Item*)GetRoom()->Find(args[4] + " " + args[5], EntityType::ITEM);
		}
	}

	if (item != nullptr)
	{
		if (item->contentsLocked == true)
		{
			if (item->key == key)
			{
				cout << "\nYou open this item with your key. You can now see its contents when you look at it." << endl;
				for (vector<Entity*>::const_iterator it = item->container.begin(); it != item->container.cend(); ++it)
				{
					Item* i = (Item*)*it;
					if (i->hidden == true)
					{
						i->hidden = false;
					}
				}
			}
			else
			{
				cout << "\nYou can't open this item, it's locked." << endl;
			}
		}
		else
		{
			for (vector<Entity*>::const_iterator it = item->container.begin(); it != item->container.cend(); ++it)
			{
				Item* i = (Item*)*it;
				if (i->hidden == true)
				{
					i->hidden = false;
				}
			}
			cout << "\nThis item is now open. You can now look at its contents." << endl;
		}
	}
	else
	{
		cout << "\nThis item doesn't exist." << endl;
	}
}

void Player::Take(const std::vector<std::string>& args)
{
	Item* item;
	switch (args.size())
	{
	case 0:
	case 1:
		return; //Error, should never happen
	case 2:
		item = (Item*) GetRoom()->Find(args[1], EntityType::ITEM);
	
		if (item != nullptr)
		{
			if (item->hidden == false)
			{
				if (item->takeable == true)
				{
					cout << "\nYou take the " << item->name << "." << endl;
					item->ChangeParentTo(this);
				}
				else
				{
					cout << "\nYou can't take the " << item->name << "." << endl;
				}
			}
			return;
		}

		cout << "\nCan't find this entity." << endl;
		return;
	case 3:
		item = (Item*)GetRoom()->Find(args[1] + " " + args[2], EntityType::ITEM);

		if (item != nullptr)
		{
			if (item->hidden == false)
			{
				if (item->takeable == true)
				{
					cout << "\nYou take the " << item->name << "." << endl;
					item->ChangeParentTo(this);
				}
				else
				{
					cout << "\nYou can't take the " << item->name << "." << endl;
				}
			}
			return;
		}

		cout << "\nCan't find this entity." << endl;
		return;
	default:
		return; //Error, should never happen
	}
}

void Player::Unlock(const std::vector<std::string>& args)
{
	Exit* exit = nullptr;
	Item* key = nullptr;
	string keyName;

	switch (args.size())
	{
	case 4:
		if (Same(args[2], "with"))
		{
			exit = (Exit*)GetRoom()->GetExit(args[1]);
			key = (Item*)Find(args[3], EntityType::ITEM);
			keyName = args[3];
		}
		break;
	case 5:
		if (Same(args[2], "with"))
		{
			exit = (Exit*)GetRoom()->GetExit(args[1]);
			key = (Item*)GetRoom()->Find(args[3] + " " + args[4], EntityType::ITEM);
			keyName = args[3] + " " + args[4];
		}
	}

	if (exit != nullptr)
	{
		if (exit->locked == true)
		{
			if (key == nullptr)
			{
				cout << "\nYou don't have the item " << keyName << endl;
				return;
			}
			if (exit->key == key)
			{
				cout << "\nYou open the exit to the " << args[1] <<  "with the " << keyName << ". You can now go through it." << endl;
				exit->locked = false;
			}
			else
			{
				cout << "\nThe " << keyName << " is not the key for the exit to the " << args[1] << "." << endl;
 			}
		}
		else
		{
			
			cout << "\nThe exit to the " << keyName << " is not locked." << endl;
		}
	}
	else
	{
		cout << "\nThere is no exit to the " << args[1] << endl;
	}
}
