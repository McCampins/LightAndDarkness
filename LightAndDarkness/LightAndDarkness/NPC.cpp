#include <iostream>

#include "NPC.h"

using namespace std;

NPC::NPC(const char * name, const char * description, Room * room, const char* state, const char* touchPhrase) :
	Creature(name, description, room, state), touchPhrase(touchPhrase)
{
	type = EntityType::NPC;
}

NPC::~NPC()
{
}

void NPC::Touch() const
{
	cout << "\n" << touchPhrase << endl;
}

