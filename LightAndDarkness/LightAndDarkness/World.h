#ifndef __World__
#define __World__

#include <vector>

class Entity;
class Player;

class World
{
public:
	World();
	~World();

public:
	std::vector<Entity*> entities;
	Player* player = nullptr;
};

#endif

