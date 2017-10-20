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

/*
void Creature::Look(const vector<string>& args) const
{
	cout << name << endl;
	cout << description << endl;
}
*/

void Creature::Go(const std::vector<std::string>& args)
{
	Exit* exit = GetRoom()->GetExit(args[1]);

	if (exit == nullptr)
		return;

	if (PlayerInRoom())
		cout << name << " moves " << args[1] << "." << endl;
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
