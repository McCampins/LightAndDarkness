#include <iostream>

#include <assert.h>

#include "Exit.h"
#include "Room.h"

using namespace std;

Exit::Exit(const char* name, const char* oppositeName, const char* description, Room* origin, Room* dest,
	bool oneWay, bool locked, bool closed, Entity* key) :
	Entity(name, description, (Entity*)origin),
	oppositeName(oppositeName), destination(dest), oneWay(oneWay), locked(locked), closed(closed), key(key)
{
	type = EntityType::EXIT;

	if (oneWay == false)
	{
		destination->container.push_back(this);
	}
}

Exit::~Exit()
{
}

void Exit::Look() const
{
	cout << name << " to " << oppositeName << endl;
	cout << description << endl;
}

const string & Exit::GetNameFrom(const Room * room) const
{
	assert(room != nullptr);

	if (room == (Room*)parent)
		return name;
	if (room == destination)
		return oppositeName;

	return name; //Error, hopefully we will never reach this statement
}

Room * Exit::GetDestinationFrom(const Room * room) const
{
	assert(room != nullptr);

	if (room == (Room*)parent)
		return destination;
	if (room == destination && !oneWay)
		return (Room*)parent;

	return nullptr; //Error
}


