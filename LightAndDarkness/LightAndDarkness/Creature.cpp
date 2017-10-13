#include <iostream>

#include "Creature.h"

Creature::Creature(const char* name, const char* description, Room* room) : 
	Entity(name, description, (Entity*) room)
{
	type = EntityType::CREATURE;
}


Creature::~Creature()
{
}

void Creature::Look(const vector<string>& args) const
{
	cout << name << endl;
	cout << description << endl;
}