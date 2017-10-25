#include <iostream>

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
			if ((*it)->type == EntityType::ITEM || (*it)->type == EntityType::PLAYER)
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
			key = (Item*)Find(args[3], EntityType::ITEM);
		}
		break;
	case 5:
		if (Same(args[3], "with"))
		{
			item = (Item*)GetRoom()->Find(args[1] + " " + args[2], EntityType::ITEM);
			key = (Item*)Find(args[4], EntityType::ITEM);
		}
		break;
	case 6:
		if (Same(args[3], "with"))
		{
			item = (Item*)GetRoom()->Find(args[1] + " " + args[2], EntityType::ITEM);
			key = (Item*)Find(args[4] + " " + args[5], EntityType::ITEM);
		}
	}

	if (item != nullptr)
	{
		if (item->contentsLocked == true)
		{
			if (key != nullptr)
			{
				if (item->key == key)
				{
					cout << "\nYou open the item " << item->name << " with your key " << key->name << ". You can now see its contents when you look at it." << endl;
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
					cout << "\nThe key " << key->name << " can't open the item " << item->name << ", it stays locked." << endl;
				}
			}
			else
			{
				cout << "\nCan't find the key. Check inventory." << endl;
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
			cout << "\nThe item " << item->name << " is open. You can now look at its contents." << endl;
		}
	}
	else
	{
		cout << "\nCan't find the item in this room." << endl;
	}
}

void Player::Take(const std::vector<std::string>& args)
{
	Item* item = nullptr;

	switch (args.size())
	{
	case 2:
		item = (Item*)GetRoom()->Find(args[1], EntityType::ITEM);
		break;
	case 3:
		item = (Item*)GetRoom()->Find(args[1] + " " + args[2], EntityType::ITEM);
		break;
	default:
		return; //Error, should never happen
	}

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
	else
	{
		cout << "\nCan't find this entity." << endl;
	}
}

void Player::Unlock(const std::vector<std::string>& args)
{
	Exit* exit = nullptr;
	Item* key = nullptr;

	switch (args.size())
	{
	case 4:
		if (Same(args[2], "with"))
		{
			exit = (Exit*)GetRoom()->GetExit(args[1]);
			key = (Item*)Find(args[3], EntityType::ITEM);
		}
		break;
	case 5:
		if (Same(args[2], "with"))
		{
			exit = (Exit*)GetRoom()->GetExit(args[1]);
			key = (Item*)Find(args[3] + " " + args[4], EntityType::ITEM);
		}
		break;
	default:
		return; //Error, should never happen
	}

	if (exit != nullptr)
	{
		if (exit->locked == true)
		{
			if (key == nullptr)
			{
				cout << "\nCan't find the key. Check inventory." << endl;
				return;
			}
			if (exit->key == key)
			{
				cout << "\nYou open the exit to the " << exit->name << " with the " << key->name << ". You can now go through it." << endl;
				exit->locked = false;
			}
			else
			{
				cout << "\nThis " << key->name << " is not the key for the exit to the " << exit->name << "." << endl;
			}
		}
		else
		{
			cout << "\nThe exit to the " << exit->name << " is not locked." << endl;
		}
	}
	else
	{
		cout << "\nThere is no exit to the " << exit->name << endl;
	}
}

void Player::Inventory() const
{
	list<Entity*> playerItems;
	FindAll(EntityType::ITEM, playerItems);

	if (playerItems.size() == 0)
	{
		cout << "\nYou are not carrying any items!" << endl;
		return;
	}

	cout << "\n";
	for (list<Entity*>::const_iterator it = playerItems.begin(); it != playerItems.cend(); ++it)
	{
		cout << "You have a " << (*it)->name << "." << endl;
	}
}

void Player::Drop(const std::vector<std::string>& args)
{
	Item* droppedItem = nullptr;
	Item* container = nullptr;

	switch (args.size())
	{
	case 2:
		droppedItem = (Item*)Find(args[1], EntityType::ITEM);
		break;
	case 3:
		droppedItem = (Item*)Find(args[1] + " " + args[2], EntityType::ITEM);
		break;
	case 4:
		if (Same(args[2], "into"))
		{
			droppedItem = (Item*)Find(args[1], EntityType::ITEM);
			container = (Item*)GetRoom()->Find(args[3], EntityType::ITEM);
		}
		break;
	case 5:
		if (Same(args[3], "into"))
		{
			droppedItem = (Item*)Find(args[1] + " " + args[2], EntityType::ITEM);
			container = (Item*)GetRoom()->Find(args[4], EntityType::ITEM);
		}
		break;
	case 6:
		if (Same(args[3], "into"))
		{
			droppedItem = (Item*)Find(args[1] + " " + args[2], EntityType::ITEM);
			container = (Item*)GetRoom()->Find(args[4] + " " + args[5], EntityType::ITEM);
		}
	}

	if (droppedItem != nullptr)
	{
		if (args.size() > 3)
		{
			if (container != nullptr)
			{
				cout << "\nYou drop the item " << droppedItem->name << " into the " << container->name << "." << endl;
			}
			else
			{
				cout << "\nThe container where you want to drop the item " << droppedItem->name << " can't be found in this room or "
					"in your inventory." << endl;
			}
		}
		else
		{
			cout << "\nYou drop the item " << droppedItem->name << " in this room." << endl;
			droppedItem->ChangeParentTo(GetRoom());
		}
	}
	else
	{
		cout << "\nYou don't have this item. Check inventory." << endl;
	}
}
