#include <iostream>

#include "Item.h"

using namespace std;

Item::Item(const char * name, const char * description, Entity * parent, ItemType itemType, bool locked, bool hidden) :
	Entity(name, description, parent), itemType(itemType), contentsLocked(locked), hidden(hidden)
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
	cout << description << endl;

	list<Entity*> stuff;
	FindAll(EntityType::ITEM, stuff);

	if (stuff.size() > 0 && contentsLocked == false)
	{
		cout << "\nThis item contains: " << endl;

		for (list<Entity*>::const_iterator it = stuff.begin(); it != stuff.end(); ++it)
		{
			Item* item = (Item*)*it;
			if (item->hidden == false)
				cout << (*it)->name << endl;
		}
	}
}
