#ifndef __Player__
#define __Player__

#include "Creature.h"

class Player : public Creature
{
public:
	Player(const char* name, const char* description, Room* room);
	~Player();

	void Look(const std::vector<std::string>& args) const;
};

#endif
