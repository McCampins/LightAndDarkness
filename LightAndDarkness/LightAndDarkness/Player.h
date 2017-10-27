#ifndef __Player__
#define __Player__

#include "Creature.h"

class Player : public Creature
{
public:
	Player(const char* name, const char* description, Room* room);
	~Player();

	void Look(const std::vector<std::string>& args) const;
	void Go(const std::vector<std::string>& args);
	void Open(const std::vector<std::string>& args) const;
	void Take(const std::vector<std::string>& args);
	void Unlock(const std::vector<std::string>& args) const;
	void Inventory() const;
	void Drop(const std::vector<std::string>& args);
	void Touch(const std::vector<std::string>& args) const;
	void Tick();

public:
	Room* previousLocation = nullptr;
};

#endif
