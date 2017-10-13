#include "World.h"

World::World()
{
}

World::~World()
{
	for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
	{
		delete *it;
	}

	entities.clear();
}
