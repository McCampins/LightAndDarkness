#ifndef __World__
#define __World__

#include <vector>

#include <time.h>

#define STATE_TICK_FREQUENCY 60.0f

class Entity;
class Player;
class NPC;

class World
{
public:
	World();
	~World();

	bool Tick(std::vector<std::string>& args);
	bool ParseCommand(std::vector<std::string>& args);
	void GameLoop();

public:
	clock_t tickTimer;
	std::vector<Entity*> entities;
	Player* player;
	NPC* god;
};

#endif

