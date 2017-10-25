#include <iostream>

#include "Item.h"
#include "Globals.h"

using namespace std;

Item::Item(const char * name, const char * description, Entity * parent, ItemType itemType, bool locked, bool openToSee, bool notVisible, bool takeable, Entity* key) :
	Entity(name, description, parent), itemType(itemType), contentsLocked(locked), openToSee(openToSee), notVisible(notVisible), takeable(takeable), key(key)
{
	type = EntityType::ITEM;
}

Item::~Item()
{
}

void Item::Look() const
{
	cout << "\n---------------" << endl;
	cout << name << endl;
	cout << "---------------" << endl;
	cout << description << "\n" << endl;

	list<Entity*> stuff;
	FindAll(EntityType::ITEM, stuff);

	if (stuff.size() > 0)
	{
		if (contentsLocked == true)
		{
			cout << "This item is locked." << endl;
		}
		else
		{
			bool allItemsClosed = true;
			bool allNotVisible = true;
			for (list<Entity*>::const_iterator it = stuff.begin(); it != stuff.end(); ++it)
			{
				Item* item = (Item*)*it;
				if (item->openToSee == false)
				{
					allItemsClosed = false;
					if (item->notVisible == false)
					{
						allNotVisible = false;
						cout << "This item contains " << (*it)->name << endl;
					}
				}
			}
			if (allItemsClosed == true)
			{
				cout << "This item is closed." << endl;
			}
			else if (allNotVisible == true)
			{
				cout << "You can't see anything on this item." << endl;
			}
		}
	}
	else
	{
		cout << "This item doesn't contain anything." << endl;
	}
}

void Item::Tick()
{
	if (Same(name, "Flower Pot"))
	{
		bool lemonSeeds = false;
		bool water = false;
		vector<Entity*>::const_iterator lemonIterator = container.end();

		for (vector<Entity*>::const_iterator it = container.begin(); it != container.cend(); ++it)
		{
			Item* item = (Item*)*it;
			if (Same(item->name, "Lemon Seeds"))
			{
				lemonSeeds = true;
			}
			else if (Same(item->name, "Water"))
			{
				water = true;
			}
			else if (Same(item->name, "Lemon"))
			{
				lemonIterator = it;
			}
		}

		if (lemonIterator != container.end())
		{
			Item* lemon = (Item*)*lemonIterator;

			if (lemon->notVisible == true)
			{
				if (lemonSeeds == true && water == true)
				{
					cout << "\nThe water, the seeds and the soil magically merge together and a beautiful but tiny lemon tree grows. One single lemon "
						"surrounded by green leaves stares at you." << endl;

					lemon->notVisible = false;

					cout << "\n> ";
				}
			}
		}
	}
}
