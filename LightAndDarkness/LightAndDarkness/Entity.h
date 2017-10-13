#ifndef __Entity__
#define __Entity__

#include <string>
#include <list>
#include <vector>

using namespace std;

enum class EntityType
{
	ENTITY,
	CREATURE,
	PLAYER,
	EXIT,
	ROOM,
	ITEM
};

class Entity
{
public:
	Entity(const char* name, const char* description, Entity* parent);
	~Entity();

	virtual void Look() const;

	void ChangeParentTo(Entity* newParent);

	void FindAll(EntityType type, list<Entity*>& listToFill) const;

public:
	EntityType type;
	string name;
	string description;
	Entity* parent;
	vector<Entity*> container;
};

#endif
