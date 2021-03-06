#ifndef __Room__
#define __Room__

#include <string>

#include "Entity.h"

class Exit;

class Room : public Entity
{
public:
	Room(const char* name, const char* description);
	~Room();

	void Look() const;

	Exit* GetExit(const std::string& direction) const;
};

#endif
