#include <iostream>

#include "World.h"
#include "Entity.h"
#include "Room.h"
#include "Exit.h"
#include "Player.h"
#include "NPC.h"
#include "Globals.h"

using namespace std;

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
		"table with six holes on top. The rest of the room is well lit and white clean.");
	Room* godRoom = new Room("God Room", "You are inside a huge room, you can barely see its end. You feel raw power emanating from "
		"its center, where a flowing creature stands. You hear it whispering \"Come closer, bring me the light...\"");

	Exit* ex1 = new Exit("North", "South", "Light Door", redRoom, orangeRoom, false, true);
	Exit* ex2 = new Exit("South", "North", "Light Door", redRoom, yellowRoom, false, true);
	Exit* ex3 = new Exit("West", "East", "Narrow Passage", centerRoom, redRoom);
	Exit* ex4 = new Exit("South", "North", "Narrow Passage", corpseRoom, centerRoom, true);
	Exit* ex5 = new Exit("South", "North", "Light Door", centerRoom, godRoom, false, true);
	Exit* ex6 = new Exit("East", "West", "Light Door", centerRoom, greenRoom, false, true);
	Exit* ex7 = new Exit("North", "South", "Light Door", greenRoom, blueRoom, false, true);
	Exit* ex8 = new Exit("South", "North", "Light Door", greenRoom, violetRoom, false, true);

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

	player = new Player("Light corpse", "You are a floating smoke-like creature, with a small light flickering inside you.",
		corpseRoom, "\nThe light inside you flickers, you feel a small pull inside, urging you to hurry.");

	entities.push_back(player);

	god = new NPC("Light God", "You see a flowing creature emanating light towards all directions. Your flickering light seems "
		"synced with the creature's.", godRoom, "\nYou hear a whispering sound coming through the light, "
		"\"Hurry, you must bring me the light\"");

	entities.push_back(god);
}


World::~World()
{
	for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
	{
		delete *it;
	}

	entities.clear();
}

bool World::Tick(std::vector<std::string>& args)
{
	bool ret = true;

	if (args.size() > 0 && args[0].length() > 0)
		ret = ParseCommand(args);

	GameLoop();

	return ret;
}

bool World::ParseCommand(std::vector<std::string>& args)
{
	bool ret = true;

	switch (args.size())
	{
	case 1:
		if (Same(args[0], "look"))
		{
			player->Look(args);
		}
		else if (Same(args[0], "north") || Same(args[0], "n"))
		{
			args.push_back("north");
			player->Go(args);
		}
		else if (Same(args[0], "east") || Same(args[0], "e"))
		{
			args.push_back("east");
			player->Go(args);
		}
		else if (Same(args[0], "south") || Same(args[0], "s"))
		{
			args.push_back("south");
			player->Go(args);
		}
		else if (Same(args[0], "west") || Same(args[0], "w"))
		{
			args.push_back("west");
			player->Go(args);
		}
		else
		{
			ret = false;
		}
		break;
	case 2:
		if (Same(args[0], "look"))
		{
			player->Look(args);
		}
		else if (Same(args[0], "go"))
		{
			if (Same(args[1], "left"))
			{
				args[1] = "west";
			}
			else if (Same(args[1], "right"))
			{
				args[1] = "east";
			}
			player->Go(args);
		}
		break;
	case 3:
		if (Same(args[0], "look"))
		{
			args[1] = args[1] + " " + args[2];
			player->Look(args);
		}
		break;
	default:
		ret = false;
	}

	return ret;
}

void World::GameLoop()
{
	clock_t now = clock();

	if ((now - tickTimer) / CLOCKS_PER_SEC > STATE_TICK_FREQUENCY)
	{
		for (vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
			if ((*it)->type == EntityType::PLAYER || (*it)->type == EntityType::NPC)
				(*it)->Tick();

		tickTimer = now;
	}
}


