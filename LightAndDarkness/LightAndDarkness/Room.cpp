#include <iostream>

#include <assert.h>

#include "Room.h"
#include "Exit.h"
#include "Item.h"
#include "Creature.h"
#include "Globals.h"

using namespace std;

Room::Room(const char* name, const char* description) : Entity(name, description, nullptr)
{
	type = EntityType::ROOM;
}

Room::~Room()
{
}

void Room::Look() const
{
	cout << "\n---------------" << endl;
	cout << name << endl;
	cout << "---------------" << endl;
	cout << description << "\n" << endl;

	for (vector<Entity*>::const_iterator it = container.begin(); it != container.cend(); ++it)
	{
		if ((*it)->type == EntityType::EXIT)
		{
			Exit* exit = (Exit*)*it;
			cout << "To the " << exit->GetNameFrom(this) << " you see the " << exit->GetDestinationFrom(this)->name << endl;
		}

		else if ((*it)->type == EntityType::ITEM)
		{
			Item* item = (Item*)*it;
			if (item->hidden == false)
				cout << "\nInside the room you see a " << item->name << endl;
		}

		else if ((*it)->type == EntityType::NPC)
		{
			Creature* creature = (Creature*)*it;
			cout << "\nInside the room stands the " << creature->name << endl;
		}
	}
}

Exit * Room::GetExit(const string& direction) const
{
	for (vector<Entity*>::const_iterator it = container.begin(); it != container.cend(); ++it)
	{
		if ((*it)->type == EntityType::EXIT)
		{
			Exit* exit = (Exit*)*it;
			if (Same(exit->GetNameFrom(this), direction))
				return exit;
		}
	}
	return nullptr;
}
