#ifndef __World__
#define __World__

#include <vector>

#include <time.h>

#define STATE_CREATURE_TICK_FREQUENCY 60.0f
#define STATE_END_LIFE_FREQUENCY 300.0f
#define STATE_ITEM_TICK_FREQUENCY 1.0f
#define STATE_LOCATION_TICK_FREQUENCY 5.0f

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
	clock_t tickTimerCreature = clock();
	clock_t tickTimerEnd = clock();
	clock_t tickTimerItem = clock();
	clock_t tickTimerLocation = clock();
	std::vector<Entity*> entities;
	Player* player = nullptr;
	NPC* god = nullptr;
	bool restart = false;
	bool end = false;
};

#endif

