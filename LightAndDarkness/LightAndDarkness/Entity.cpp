#include <iostream>
#include <algorithm>

#include "Entity.h"

using namespace std;

Entity::Entity(const char* name, const char* description, Entity* parent = nullptr) :
	name(name), description(description), parent(parent)
{
	type = EntityType::ENTITY;

	if (parent != nullptr)
		parent->container.push_back(this);
}


Entity::~Entity()
{
}

void Entity::Look() const
{
	cout << name << endl;
	cout << description << endl;
}

void Entity::Tick()
{
}

void Entity::ChangeParentTo(Entity* newParent)
{
	if (parent != nullptr)
		container.erase(std::remove(container.begin(), container.end(), this), container.end());

	parent = newParent;

	if (parent != nullptr)
		parent->container.push_back(this);
}

void Entity::FindAll(EntityType type, list<Entity*>& listToFill) const
{
	for (vector<Entity*>::const_iterator it = container.begin(); it != container.cend(); ++it)
	{
		if ((*it)->type == type)
		{
			listToFill.push_back(*it);
		}
	}
}
