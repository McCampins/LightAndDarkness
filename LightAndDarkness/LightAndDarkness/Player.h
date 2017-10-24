#ifndef __Player__
#define __Player__

#include "Creature.h"

class Player : public Creature
{
public:
	Player(const char* name, const char* description, Room* room, const char* state);
	~Player();

	void Look(const std::vector<std::string>& args) const;
	void Go(const std::vector<std::string>& args);
	void Open(const std::vector<std::string>& args);
	void Take(const std::vector<std::string>& args);
};

#endif
