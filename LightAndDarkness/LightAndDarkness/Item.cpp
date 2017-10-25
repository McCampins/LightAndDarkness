#include <iostream>

#include "Item.h"

using namespace std;

Item::Item(const char * name, const char * description, Entity * parent, ItemType itemType, bool locked, bool hidden, bool takeable, Entity* key) :
	Entity(name, description, parent), itemType(itemType), contentsLocked(locked), hidden(hidden), takeable(takeable), key(key)
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
			bool allHiden = true;
			for (list<Entity*>::const_iterator it = stuff.begin(); it != stuff.end(); ++it)
			{
				Item* item = (Item*)*it;
				if (item->hidden == false)
				{
					cout << "This item contains " << (*it)->name << endl;
					allHiden = false;
				}
			}
			if (allHiden == true)
			{
				cout << "This item is closed." << endl;
			}
		}
	}
	else
	{
		cout << "This item doesn't contain anything." << endl;
	}
}
