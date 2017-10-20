#ifndef __Creature__
#define __Creature__

#include <vector>
#include <string>

#include "Entity.h"

class Room;

class Creature : public Entity
{
public:
	Creature(const char* name, const char* description, Room* room, const char* state);
	~Creature();

	//virtual void Look(const std::vector<std::string>& args) const;
	virtual void Go(const std::vector<std::string>& args);
	void Tick();

	Room* GetRoom() const;
	bool PlayerInRoom() const;

public:
	std::string stateSentence;
};

#endif

