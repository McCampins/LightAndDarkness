#ifndef __NPC__
#define __NPC__

#include "Creature.h"

class NPC : public Creature
{
public:
	NPC(const char* name, const char* description, Room* room, const char* state, const char* touchPhrase);
	~NPC();

	void Touch() const;

public:
	std::string touchPhrase;
};

#endif

