#ifndef __Item__
#define __Item__

#include "Entity.h"

enum class ItemType
{
	LIGHTBALL,
	WHITEBALL,
	KEY,
	COMMON,
};

class Item : public Entity
{
public:
	Item(const char* name, const char* description, Entity* parent, ItemType itemType = ItemType::COMMON, bool locked = false,
		bool openToSee = false, bool notVisible = false, bool takeable = false, Entity* key = nullptr);
	~Item();

	void Look() const;
	void Tick();

public:
	ItemType itemType;
	bool contentsLocked;
	bool openToSee;
	bool notVisible;
	bool takeable;
	Entity* key;
};

#endif
