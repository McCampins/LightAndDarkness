#include "World.h"
#include "Entity.h"
#include "Room.h"
#include "Exit.h"
#include "Player.h"

World::World()
{

	Room* orangeRoom = new Room("Orange Room", "You are inside a small room, dimly lighted with two orange lamps.");
	Room* redRoom = new Room("Red Room", "You are inside a small room, dimly lighted with one red lamps.");
	Room* yellowRoom = new Room("Yellow Room", "You are inside a small room, dimly lighted with three yellow lamps.");
	Room* greenRoom = new Room("Green Room", "You are inside a small room, dimly ligthed with four green lamps.");
	Room* blueRoom = new Room("Blue Room", "You are inside a small room, dimly lighted with five blue lamps.");
	Room* violetRoom = new Room("Violet Room", "You are inside a small room, dimly lighted with six violet lamps.");

	Room* corpseRoom = new Room("Corpse Room", "You are inside a wide room, empty and dark. You feel like you just woke up. Next to you "
	"you see dozens of other creatures like you, all laying motionless on the ground.");
	Room* centerRoom = new Room("Center Room", "You are inside a large circular room. Right in the center there's a cylindrical "
		"table with six holes on top. The rest of the room is well lit and surgically white clean.");
	Room* godRoom = new Room("God Room", "You are inside a huge room, you can barely see its end. You feel raw power emanating from "
		"its center, where a flowing creature stands. You hear it whispering \"Come closer, bring me the ligth...\"");

	Exit* ex1 = new Exit("North", "South", "Light Door", redRoom, orangeRoom);
	Exit* ex2 = new Exit("South", "North", "Light Door", redRoom, yellowRoom);
	Exit* ex3 = new Exit("East", "West", "Narrow Passage", centerRoom, redRoom);
	Exit* ex4 = new Exit("South", "North", "Narrow Passage", corpseRoom, centerRoom);
	Exit* ex5 = new Exit("South", "North", "Light Door", centerRoom, godRoom);
	Exit* ex6 = new Exit("East", "West", "Light Door", centerRoom, greenRoom);
	Exit* ex7 = new Exit("North", "South", "Light Door", greenRoom, blueRoom);
	Exit* ex8 = new Exit("South", "North", "Light Door", greenRoom, violetRoom);

	entities.push_back(orangeRoom);
	entities.push_back(redRoom);
	entities.push_back(yellowRoom);
	entities.push_back(greenRoom);
	entities.push_back(blueRoom);
	entities.push_back(violetRoom);
	entities.push_back(corpseRoom);
	entities.push_back(centerRoom);
	entities.push_back(godRoom);
	entities.push_back(ex1);
	entities.push_back(ex2);
	entities.push_back(ex3);
	entities.push_back(ex4);
	entities.push_back(ex5);
	entities.push_back(ex6);
	entities.push_back(ex7);
	entities.push_back(ex8);

	Player* player = new Player("Light corpse", "You are a floating smoke-like creature, with a small light flickering inside you.", corpseRoom);
}

World::~World()
{
	for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
	{
		delete *it;
	}

	entities.clear();
}

bool World::Tick(std::vector<std::string>& args) const
{
	bool ret = true;

	/*
	if (args.size() > 0 && args[0].length() > 0)
		ret = ParseCommand(args);

	GameLoop();
	*/

	return ret;
}
