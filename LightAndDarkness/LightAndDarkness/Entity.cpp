#include <iostream>
#include <algorithm>

#include "Entity.h"
#include "Item.h"
#include "Globals.h"

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
		parent->container.erase(std::remove(parent->container.begin(), parent->container.end(), this), parent->container.end());

	parent = newParent;

	if (parent != nullptr)
		parent->container.push_back(this);
}

bool Entity::Find(Entity* entity) const
{
	for (vector<Entity*>::const_iterator it = container.begin(); it != container.cend(); ++it)
	{
		if ((*it) == entity)
			return true;
	}

	return false;
}

Entity* Entity::Find(EntityType type) const
{
	for (vector<Entity*>::const_iterator it = container.begin(); it != container.cend(); ++it)
	{
		if ((*it)->type == type)
			return *it;
	}

	return nullptr;
}

Entity* Entity::Find(const string& name, EntityType type) const
{
	for (vector<Entity*>::const_iterator it = container.begin(); it != container.cend(); ++it)
	{
		if ((*it)->type == type)
		{
			if (Same((*it)->name, name))
				return *it;
		}
		if ((*it)->container.empty() == false)
		{
			Entity* result = (*it)->Find(name, type);
			if (result != nullptr)
				return result;
		}
	}

	return nullptr;
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
