#include <iostream>

#include "Item.h"

using namespace std;

Item::Item(const char * name, const char * description, Entity * parent, ItemType itemType) :
	Entity(name, description, parent), itemType(itemType)
{
	type = EntityType::ITEM;
}

Item::~Item()
{
}

void Item::Look() const
{
	cout << name << endl;
	cout << description << endl;

	list<Entity*> stuff;
	FindAll(EntityType::ITEM, stuff);

	if (stuff.size() > 0) {
		cout << "This item contains: " << endl;

		for (list<Entity*>::const_iterator it = stuff.begin(); it != stuff.end(); ++it)
		{
			cout << (*it)->name << endl;
		}
	}
}
