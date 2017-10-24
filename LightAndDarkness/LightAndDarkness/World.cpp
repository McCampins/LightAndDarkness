#include <iostream>

#include "World.h"
#include "Entity.h"
#include "Room.h"
#include "Exit.h"
#include "Player.h"
#include "NPC.h"
#include "Globals.h"
#include "Item.h"

using namespace std;

World::World()
{
	restart = false;

	//Rooms
	Room* redRoom = new Room("Red Room", "You are inside a small room, dimly lighted with one red lamp. When you enter you hear a faint "
		"echo through the light: \"No mind can wander too far, a sense of balance must be met to advance...\"");
	Room* orangeRoom = new Room("Orange Room", "You are inside a small room, dimly lighted with two orange lamps.");
	Room* yellowRoom = new Room("Yellow Room", "You are inside a small room, dimly lighted with three yellow lamps.");
	Room* greenRoom = new Room("Green Room", "You are inside a small room, dimly ligthed with four green lamps.");
	Room* blueRoom = new Room("Blue Room", "You are inside a small room, dimly lighted with five blue lamps.");
	Room* violetRoom = new Room("Violet Room", "You are inside a small room, dimly lighted with six violet lamps.");

	Room* corpseRoom = new Room("Corpse Room", "You are inside a wide room, empty and dark. You feel like you just woke up. Next to you "
		"you see dozens of other creatures like you, all laying motionless on the ground.");
	Room* centerRoom = new Room("Center Room", "You are inside a large circular room. The room is well lit and white clean.");
	Room* godRoom = new Room("God Room", "You are inside a huge room, you can barely see its end. You feel raw power emanating from "
		"its center, where a flowing creature stands. You hear it whispering \"Come closer, bring me the light...\"");

	entities.push_back(redRoom);
	entities.push_back(orangeRoom);
	entities.push_back(yellowRoom);
	entities.push_back(greenRoom);
	entities.push_back(blueRoom);
	entities.push_back(violetRoom);
	entities.push_back(corpseRoom);
	entities.push_back(centerRoom);
	entities.push_back(godRoom);

	//Color room keys
	Item* yellowKey = new Item("Yellow Key", "A small yellow key", nullptr, ItemType::KEY);
	Item* greenKey = new Item("Green Key", "A small green key", nullptr, ItemType::KEY);
	Item* blueKey = new Item("Blue Key", "A small blue key", nullptr, ItemType::KEY);
	Item* violetKey = new Item("Violet Key", "A small violet key", nullptr, ItemType::KEY);

	entities.push_back(yellowKey);
	entities.push_back(greenKey);
	entities.push_back(blueKey);
	entities.push_back(violetKey);

	//Light balls given in each color room
	Item* redBall = new Item("Red Ball", "A ball of condensed red light", nullptr, ItemType::LIGHTBALL);
	Item* orangeBall = new Item("Orange Ball", "A ball of condensed orange light", nullptr, ItemType::LIGHTBALL);
	Item* yellowBall = new Item("Yellow Ball", "A ball of condensed yellow light", nullptr, ItemType::LIGHTBALL);
	Item* greenBall = new Item("Green Ball", "A ball of condensed green light", nullptr, ItemType::LIGHTBALL);
	Item* blueBall = new Item("Blue Ball", "A ball of condensed blue light", nullptr, ItemType::LIGHTBALL);
	Item* violetBall = new Item("Violet Ball", "A ball of condensed violet light", nullptr, ItemType::LIGHTBALL);

	entities.push_back(redBall);
	entities.push_back(orangeBall);
	entities.push_back(yellowBall);
	entities.push_back(greenBall);
	entities.push_back(blueBall);
	entities.push_back(violetBall);

	//Center room
	Item* stonePillar = new Item("Stone Pillar", "A cylindrical table made of stone with six holes on top. The holes are lined up in the "
		"center of the table, from left to right. Over them there is a rainbow with an angel on each side. "
		"Under the six holes, there is an inverted rainbow with a demon on each side. Both rainbows are carved delicately in the stone.",
		centerRoom, ItemType::COMMON);
	Item* redHole = new Item("Red Hole", "A faint red light is coming from the seamingly endless bottom of the hole.", stonePillar,
		ItemType::COMMON);
	Item* orangeHole = new Item("Orange Hole", "A faint orange light is coming from the seamingly endless bottom of the hole.", stonePillar,
		ItemType::COMMON);
	Item* yellowHole = new Item("Yellow Hole", "A faint yellow light is coming from the seamingly endless bottom of the hole.", stonePillar,
		ItemType::COMMON);
	Item* greenHole = new Item("Green Hole", "A faint green light is coming from the seamingly endless bottom of the hole.", stonePillar,
		ItemType::COMMON);
	Item* blueHole = new Item("Blue Hole", "A faint blue light is coming from the seamingly endless bottom of the hole.", stonePillar,
		ItemType::COMMON);
	Item* violetHole = new Item("Violet Hole", "A faint violet light is coming from the seamingly endless bottom of the hole.", stonePillar,
		ItemType::COMMON);
	Item* whiteBall = new Item("White Ball", "A ball of condensed light.", centerRoom, ItemType::WHITEBALL, false, true);
	Item* blackBall = new Item("Black Ball", "A ball of condensed darkness.", centerRoom, ItemType::BLACKBALL, false, true);

	entities.push_back(stonePillar);
	entities.push_back(redHole);
	entities.push_back(orangeHole);
	entities.push_back(yellowHole);
	entities.push_back(greenHole);
	entities.push_back(blueHole);
	entities.push_back(violetHole);
	entities.push_back(whiteBall);
	entities.push_back(blackBall);

	//Red Room
	Item* redTable = new Item("Red Table", "A wooden old table, standing in the middle of the room.", redRoom, ItemType::COMMON);
	Item* leftRedChest = new Item("Left Chest", "A wooden chest, no lock can be seen.", redTable, ItemType::COMMON);
	Item* centerRedChest = new Item("Center Chest", "A wooden chest, no lock can be seen.", redTable, ItemType::COMMON);
	Item* rightRedChest = new Item("Right Chest", "A wooden chest, no lock can be seen.", redTable, ItemType::COMMON);
	Item* orangeKey1 = new Item("Orange Key", "A small orange key. It was stored on the left chest", leftRedChest, ItemType::KEY, false, true);
	Item* orangeKey2 = new Item("Orange Key", "A small orange key. It was stored on the center chest", centerRedChest, ItemType::KEY, false, true);
	Item* orangeKey3 = new Item("Orange Key", "A small orange key. It was stored on the right chest", rightRedChest, ItemType::KEY, false, true);

	entities.push_back(redTable);
	entities.push_back(leftRedChest);
	entities.push_back(centerRedChest);
	entities.push_back(rightRedChest);
	entities.push_back(orangeKey1);
	entities.push_back(orangeKey2);
	entities.push_back(orangeKey3);

	//Exits
	Exit* ex1 = new Exit("North", "South", "Light Door", redRoom, orangeRoom, false, true, orangeKey2);
	Exit* ex2 = new Exit("South", "North", "Light Door", redRoom, yellowRoom, false, true);
	Exit* ex3 = new Exit("West", "East", "Narrow Passage", centerRoom, redRoom);
	Exit* ex4 = new Exit("South", "North", "Narrow Passage", corpseRoom, centerRoom, true);
	Exit* ex5 = new Exit("South", "North", "Light Door", centerRoom, godRoom, false, true);
	Exit* ex6 = new Exit("East", "West", "Light Door", centerRoom, greenRoom, false, true);
	Exit* ex7 = new Exit("North", "South", "Light Door", greenRoom, blueRoom, false, true);
	Exit* ex8 = new Exit("South", "North", "Light Door", greenRoom, violetRoom, false, true);

	entities.push_back(ex1);
	entities.push_back(ex2);
	entities.push_back(ex3);
	entities.push_back(ex4);
	entities.push_back(ex5);
	entities.push_back(ex6);
	entities.push_back(ex7);
	entities.push_back(ex8);

	//Player
	player = new Player("Light corpse", "You are a floating smoke-like creature, with a small light flickering inside you.",
		corpseRoom, "\nThe light inside you flickers, you feel a small pull inside, urging you to hurry.");

	entities.push_back(player);

	//NPC God
	god = new NPC("Light God", "You see a flowing creature emanating light towards all directions. Your flickering light seems "
		"synced with the creature's.", godRoom, "\nYou hear a whispering sound coming through the light, "
		"\"Hurry, you must bring me the light...\"");

	entities.push_back(god);
}


World::~World()
{
	for (std::vector<Entity*>::reverse_iterator it = entities.rbegin(); it != entities.rend(); ++it)
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
		if (Same(args[0], "open"))
		{
			player->Open(args);
		}
		if (Same(args[0], "take"))
		{
			player->Take(args);
		}
		break;
	case 3:
		if (Same(args[0], "look"))
		{
			player->Look(args);
		}
		if (Same(args[0], "open"))
		{
			player->Open(args);
		}
		if (Same(args[0], "take"))
		{
			player->Take(args);
		}
		break;
	case 4:
		if (Same(args[0], "open"))
		{
			player->Open(args);
		}
		break;
	case 5:
		if (Same(args[0], "open"))
		{
			player->Open(args);
		}
		break;
	case 6:
		if (Same(args[0], "open"))
		{
			player->Open(args);
		}
	default:
		ret = false;
	}

	return ret;
}

void World::GameLoop() 
{
	clock_t now = clock();

	if ((now - tickTimer) / CLOCKS_PER_SEC > STATE_CREATURE_TICK_FREQUENCY)
	{
		for (vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
			if ((*it)->type == EntityType::PLAYER || (*it)->type == EntityType::NPC)
				(*it)->Tick();

		tickTimer = now;
	}

	if ((now - tickTimer) / CLOCKS_PER_SEC > STATE_END_LIFE_FREQUENCY)
	{
		restart = true;
	}
}


