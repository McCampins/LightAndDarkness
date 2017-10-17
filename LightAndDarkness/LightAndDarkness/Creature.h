#ifndef __Creature__
#define __Creature__

#include <vector>
#include <string>

#include "Entity.h"

class Room;

class Creature : public Entity
{
public:
	Creature(const char* name, const char* description, Room* room);
	~Creature();

	virtual void Look(const std::vector<std::string>& args) const;

public:

	Room* location;
};

#endif

