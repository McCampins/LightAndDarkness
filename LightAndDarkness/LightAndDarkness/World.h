#ifndef __World__
#define __World__

#include <vector>

using namespace std;

class Entity;
class Player;

class World
{
public:
	World();
	~World();

public:
	vector<Entity*> entities;
	Player* player;
};

#endif

