#ifndef __Exit__
#define __Exit__

#include "Entity.h"

class Room;

enum class Direction 
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};

class Exit : public Entity
{
public:
	Exit(const char* direction, const char* oppositeName, const char* description, Room* origin, Room* destination, 
		bool oneWay = false, bool locked = false, bool closed = false, Entity* key = nullptr);
	~Exit();

	void Look() const;
	const string& GetNameFrom(const Room* room) const;
	Room* GetDestinationFrom(const Room* room) const;

public:
	bool oneWay;
	bool locked;
	bool closed;
	string oppositeName;
	Room* destination;
	Entity* key;
};

#endif
