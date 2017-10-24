#ifndef __World__
#define __World__

#include <vector>

#include <time.h>

#define STATE_CREATURE_TICK_FREQUENCY 60.0f
#define STATE_END_LIFE_FREQUENCY 300.0f

class Entity;
class Player;
class NPC;

enum class ParseReturn
{
	RESTART,
	LOOK,
	NOTHING
};

class World
{
public:
	World();
	~World();

	bool Tick(std::vector<std::string>& args);
	bool ParseCommand(std::vector<std::string>& args);
	void GameLoop();

public:
	clock_t tickTimer = clock();
	std::vector<Entity*> entities;
	Player* player = nullptr;
	NPC* god = nullptr;
	bool restart = false;
};

#endif

