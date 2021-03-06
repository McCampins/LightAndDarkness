#include <iostream>

#include "World.h"
#include "Player.h"
#include "Globals.h"
#include "Exit.h"
#include "Room.h"
#include "Item.h"
#include "NPC.h"

using namespace std;

Player::Player(const char* name, const char* description, Room* room) :
	Creature(name, description, room, "")
{
	type = EntityType::PLAYER;
}


Player::~Player()
{
}

void Player::Look(const vector<string>& args) const
{
	Entity* entity = nullptr;

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

		entity = parent->Find(args[1], EntityType::ITEM);
		if (entity != nullptr)
		{
			Item* it = (Item*)entity;
			if (it->openToSee == false && it->notVisible == false)
			{
				entity->Look();
			}
			else
			{
				cout << "\nCan't find this entity." << endl;
			}
			return;
		}
		entity = parent->Find(args[1], EntityType::EXIT);
		if (entity != nullptr)
		{
			entity->Look();
			return;
		}
		entity = parent->Find(args[1], EntityType::NPC);
		if (entity != nullptr)
		{
			entity->Look();
			return;
		}

		cout << "\nCan't find this entity." << endl;
		break;
	case 3:
		entity = parent->Find(args[1] + " " + args[2], EntityType::ITEM);
		if (entity != nullptr)
		{
			Item* it = (Item*)entity;
			if (it->openToSee == false && it->notVisible == false)
			{
				entity->Look();
			}
			else
			{
				cout << "\nCan't find this entity." << endl;
			}
			return;
		}
		entity = parent->Find(args[1] + " " + args[2], EntityType::EXIT);
		if (entity != nullptr)
		{
			entity->Look();
			return;
		}
		entity = parent->Find(args[1] + " " + args[2], EntityType::NPC);
		if (entity != nullptr)
		{
			entity->Look();
			return;
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
		if (Same(args[1], "north") || Same(args[1], "west") || Same(args[1], "south") || Same(args[1], "east"))
		{
			cout << "\nThere is no exit to the " << args[1] << endl;
		}
		else
		{
			cout << "\nInvalid direction. Must be either north, east, south or west." << endl;
		}
		return;
	}

	if (exit->locked)
	{
		cout << "\nThis exit is locked." << endl;
		return;
	}

	if (exit->oneWay)
	{
		cout << "\nAs you walk through, the door locks behind you." << endl;
	}

	cout << "\nYou go through a " << exit->description << " to the " << exit->GetNameFrom((Room*)parent) << "." << endl;
	ChangeParentTo(exit->GetDestinationFrom((Room*)parent));
	parent->Look();
}

void Player::Open(const std::vector<std::string>& args) const
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
		if (Same(args[2], "with"))
		{
			item = (Item*)GetRoom()->Find(args[1], EntityType::ITEM);
			key = (Item*)Find(args[3] + " " + args[4], EntityType::ITEM);
		}
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
		if (item->openToSee == false && item->notVisible == false)
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
							if (i->openToSee == true)
							{
								i->openToSee = false;
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
				bool alreadyOpen = true;

				for (vector<Entity*>::const_iterator it = item->container.begin(); it != item->container.cend(); ++it)
				{
					Item* i = (Item*)*it;
					if (i->openToSee == true)
					{
						i->openToSee = false;
						alreadyOpen = false;
					}
				}

				if (alreadyOpen)
				{
					cout << "\nThis item cannot be opened or is already opened." << endl;
				}
				else
				{
					cout << "\nThe item " << item->name << " is open. You can now look at its contents." << endl;
				}
			}
		}
		else
		{
			cout << "\nCan't find the item in this room." << endl;
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
		item = (Item*)Find(args[1], EntityType::ITEM);
		if (item == nullptr)
		{
			item = (Item*)GetRoom()->Find(args[1], EntityType::ITEM);
		}
		else
		{
			if (item->parent->type == EntityType::PLAYER)
				item = nullptr;
		}
		break;
	case 3:
		item = (Item*)Find(args[1] + " " + args[2], EntityType::ITEM);
		if (item == nullptr)
		{
			item = (Item*)GetRoom()->Find(args[1] + " " + args[2], EntityType::ITEM);
		}
		else
		{
			if (item->parent->type == EntityType::PLAYER)
				item = nullptr;
		}
		break;
	default:
		return; //Error, should never happen
	}

	if (item != nullptr)
	{
		if (item->openToSee == false && item->notVisible == false)
		{
			if (item->takeable == true)
			{
				if (container.size() < 10)
				{
					cout << "\nYou take the " << item->name << "." << endl;
					item->ChangeParentTo(this);
					return;
				}
				else
				{
					cout << "\nYour inventory is full, must drop something before taking anything else." << endl;
					return;
				}
			}
			else
			{
				cout << "\nYou can't take the " << item->name << "." << endl;
				return;
			}
		}
	}
	cout << "\nCan't find this entity." << endl;
}

void Player::Unlock(const std::vector<std::string>& args) const
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
		else
		{
			cout << "\nSorry, I don't understand your command." << endl;
			return;
		}
		break;
	case 5:
		if (Same(args[2], "with"))
		{
			exit = (Exit*)GetRoom()->GetExit(args[1]);
			key = (Item*)Find(args[3] + " " + args[4], EntityType::ITEM);
		}
		else
		{
			cout << "\nSorry, I don't understand your command." << endl;
			return;
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
			else if (exit->key == key)
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
		if (Same(args[1], "north") || Same(args[1], "west") || Same(args[1], "south") || Same(args[1], "east"))
		{
			cout << "\nThere is no exit to the " << args[1] << endl;
		}
		else
		{
			cout << "\nInvalid direction. Must be either north, east, south or west." << endl;
		}
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
		if (Same(args[2], "into") || Same(args[2], "in"))
		{
			droppedItem = (Item*)Find(args[1], EntityType::ITEM);
			container = (Item*)GetRoom()->Find(args[3], EntityType::ITEM);
		}
		else
		{
			cout << "\nSorry, I don't understand your command." << endl;
			return;
		}
		break;
	case 5:
		if (Same(args[2], "into") || Same(args[2], "in"))
		{
			droppedItem = (Item*)Find(args[1], EntityType::ITEM);
			container = (Item*)GetRoom()->Find(args[3] + " " + args[4], EntityType::ITEM);
		}
		else if (Same(args[3], "into") || Same(args[3], "in"))
		{
			droppedItem = (Item*)Find(args[1] + " " + args[2], EntityType::ITEM);
			container = (Item*)GetRoom()->Find(args[4], EntityType::ITEM);
		}
		else
		{
			cout << "\nSorry, I don't understand your command." << endl;
			return;
		}
		break;
	case 6:
		if (Same(args[3], "into") || Same(args[3], "in"))
		{
			droppedItem = (Item*)Find(args[1] + " " + args[2], EntityType::ITEM);
			container = (Item*)GetRoom()->Find(args[4] + " " + args[5], EntityType::ITEM);
		}
		else
		{
			cout << "\nSorry, I don't understand your command." << endl;
			return;
		}
		break;
	default:
		return; //Error, should never happen
	}

	if (droppedItem != nullptr)
	{
		if (args.size() > 3)
		{
			if (container != nullptr)
			{
				if (container->openToSee == false && container->notVisible == false)
				{
					cout << "\nYou drop the " << droppedItem->name << " into the " << container->name << "." << endl;
					droppedItem->ChangeParentTo(container);
				}
			}
			else
			{
				cout << "\nThe container where you want to drop the " << droppedItem->name << " can't be found in this room or "
					"in your inventory." << endl;
			}
		}
		else
		{
			cout << "\nYou drop the " << droppedItem->name << " in this room." << endl;
			droppedItem->ChangeParentTo(GetRoom());
		}
	}
	else
	{
		cout << "\nYou don't have this item. Check inventory." << endl;
	}
}

void Player::Touch(const std::vector<std::string>& args) const
{
	if (args.size() == 3) //Should always happen
	{
		list<Entity*> npcList;
		GetRoom()->FindAll(EntityType::NPC, npcList);

		for (list<Entity*>::const_iterator it = npcList.begin(); it != npcList.end(); ++it)
		{
			if (Same((*it)->name, args[1]))
			{
				NPC* npc = (NPC*)*it;
				npc->Touch();
				return;
			}
		}

		cout << "\nThe creature you are trying to touch can't be found." << endl;
	}
}

void Player::Tick()
{
	Item* item = nullptr;

	if (GetRoom() == previousLocation)
	{
		if (previousLocation != nullptr)
		{
			if (Same(previousLocation->name, "Yellow Room"))
			{
				item = (Item*)GetRoom()->Find("Yellow Ball", EntityType::ITEM);
				if (item != nullptr)
				{
					if (item->notVisible == true)
					{
						item->notVisible = false;
						item = (Item*)GetRoom()->Find("Green Key", EntityType::ITEM);
						if (item != nullptr)
						{
							item->notVisible = false;
							cout << "\nYour patience has been rewarded. Two objects appear in the room..." << endl;
							cout << "\n> ";

						}
					}
				}
			}
		}
	}

	previousLocation = GetRoom();
}
