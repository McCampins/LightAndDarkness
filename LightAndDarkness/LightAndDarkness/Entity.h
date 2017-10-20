#ifndef __Entity__
#define __Entity__

#include <string>
#include <list>
#include <vector>

enum class EntityType
{
	ENTITY,
	CREATURE,
	PLAYER,
	NPC,
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
	virtual void Tick();

	void ChangeParentTo(Entity* newParent);

	void FindAll(EntityType type, std::list<Entity*>& listToFill) const;

public:
	EntityType type;
	std::string name;
	std::string description;
	Entity* parent;
	std::vector<Entity*> container;
};

#endif
