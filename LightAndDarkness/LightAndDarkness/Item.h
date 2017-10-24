#ifndef __Item__
#define __Item__

#include "Entity.h"

enum class ItemType
{
	LIGHTBALL,
	WHITEBALL,
	BLACKBALL,
	KEY,
	COMMON,
};

class Item : public Entity
{
public:
	Item(const char* name, const char* description, Entity* parent, ItemType itemType = ItemType::COMMON, bool locked = false,
	bool hidden = false, Entity* key = nullptr);
	~Item();

	void Look() const;

public:
	ItemType itemType;
	bool contentsLocked;
	bool hidden;
	Entity* key;
};

#endif
