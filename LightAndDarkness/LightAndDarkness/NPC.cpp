#include "NPC.h"

NPC::NPC(const char * name, const char * description, Room * room, const char* state) :
	Creature(name, description, room, state)
{
	type = EntityType::NPC;
}

NPC::~NPC()
{
}

