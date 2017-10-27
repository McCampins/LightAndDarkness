#include <iostream>

#include "Creature.h"
#include "Exit.h"
#include "Room.h"

using namespace std;

Creature::Creature(const char* name, const char* description, Room* room, const char* state) :
	Entity(name, description, (Entity*)room), stateSentence(state)
{
	type = EntityType::CREATURE;
}


Creature::~Creature()
{
}

void Creature::Look() const
{
	cout << "\n" << description << endl;
}

void Creature::Go(const std::vector<std::string>& args)
{
}

void Creature::Tick()
{
	cout << stateSentence << endl << "> ";
}

Room* Creature::GetRoom() const
{
	return (Room*)parent;
}

bool Creature::PlayerInRoom() const
{
	return parent->Find(EntityType::PLAYER) != nullptr;
}
