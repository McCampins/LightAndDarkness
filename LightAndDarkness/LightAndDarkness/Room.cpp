#include <iostream>

#include "Room.h"
#include "Exit.h"
#include "Item.h"
#include "Creature.h"
#include "Globals.h"

Room::Room(const char* name, const char* description) : Entity(name, description, NULL)
{
	type = EntityType::ROOM;
}

Room::~Room()
{
}

void Room::Look() const
{
	cout << name << endl;
	cout << description << endl;

	for (vector<Entity*>::const_iterator it = container.begin(); it != container.cend(); ++it)
	{
		if ((*it)->type == EntityType::EXIT)
		{
			Exit* exit = (Exit*)*it;
			cout << "To the " << exit->GetNameFrom(this) << " you see " << exit->GetDestinationFrom(this)->name << endl;
		}

		else if ((*it)->type == EntityType::ITEM)
		{
			Item* item = (Item*)*it;
			cout << "Inside the room you see a " << item->name << endl;
		}

		else if ((*it)->type == EntityType::CREATURE)
		{
			Creature* creature = (Creature*)*it;
			cout << "There is also the creature " << creature->name << endl;
		}
	}
}

Exit * Room::GetExit(const string & direction) const
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
	return NULL;
}
