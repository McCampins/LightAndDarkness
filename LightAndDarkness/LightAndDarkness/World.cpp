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
		"echo through the light: \"No mind can ever wander too far, a sense of balance must be met in order to advance...\"");
	Room* orangeRoom = new Room("Orange Room", "You are inside a small room, dimly lighted with two orange lamps. When you enter you hear a faint "
		"echo through the light: \"All that serves a purpose, must first grow...\"");
	Room* yellowRoom = new Room("Yellow Room", "You are inside a small room, dimly lighted with three yellow lamps. When you enter you hear a faint "
		"echo through the light: \"Patience is virtue...\"");
	Room* greenRoom = new Room("Green Room", "You are inside a small room, dimly ligthed with four green lamps. When you enter you hear a faint "
		"echo through the light: \"Quid pro quo...\"");
	Room* blueRoom = new Room("Blue Room", "You are inside a small room, dimly lighted with five blue lamps. When you enter you hear a faint "
		"echo through the light: \"We all desire what we don't have...\"");
	Room* violetRoom = new Room("Violet Room", "You are inside a small room, dimly lighted with six violet lamps. When you enter you hear a faint "
		"echo through the light: \"In the chaos of numbers, choose the ones that follow triangles...\"");

	Room* corpseRoom = new Room("Corpse Room", "You are inside a wide room, empty and dark. You feel like you just woke up. Next to you "
		"you see dozens of other creatures like you, all laying motionless on the ground. You hear a voice: \"All of them tried, none made it. "
		"Bring me the light mortal, or die trying!\"");
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

	//Center room
	Item* stonePillar = new Item("Stone Pillar", "A cylindrical table made of stone with six holes on top. The holes are lined up in the "
		"center of the table, from left to right. Over them there is a rainbow with an angel on each side. ", centerRoom, ItemType::COMMON);
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
	Item* whiteBall = new Item("White Ball", "A ball of condensed light.", centerRoom, ItemType::WHITEBALL, false, false, true, true);

	entities.push_back(stonePillar);
	entities.push_back(redHole);
	entities.push_back(orangeHole);
	entities.push_back(yellowHole);
	entities.push_back(greenHole);
	entities.push_back(blueHole);
	entities.push_back(violetHole);
	entities.push_back(whiteBall);

	//Red Room
	Item* redTable = new Item("Red Table", "A wooden old table, standing in the middle of the room.", redRoom, ItemType::COMMON);
	Item* leftRedChest = new Item("Left Chest", "A wooden chest, no lock can be seen.", redTable, ItemType::COMMON);
	Item* centerRedChest = new Item("Center Chest", "A wooden chest, no lock can be seen.", redTable, ItemType::COMMON);
	Item* rightRedChest = new Item("Right Chest", "A wooden chest, no lock can be seen.", redTable, ItemType::COMMON);
	Item* orangeKey1 = new Item("Left Key", "A small orange key. It was stored on the left chest.", leftRedChest, ItemType::KEY, false, true, false, true);
	Item* orangeKey2 = new Item("Center Key", "A small orange key. It was stored on the center chest.", centerRedChest, ItemType::KEY, false, true, false, true);
	Item* orangeKey3 = new Item("Right Key", "A small orange key. It was stored on the right chest.", rightRedChest, ItemType::KEY, false, true, false, true);
	Item* redBall = new Item("Red Ball", "A ball of condensed red light.", centerRedChest, ItemType::LIGHTBALL, false, true, false, true);

	entities.push_back(redTable);
	entities.push_back(leftRedChest);
	entities.push_back(centerRedChest);
	entities.push_back(rightRedChest);
	entities.push_back(orangeKey1);
	entities.push_back(orangeKey2);
	entities.push_back(orangeKey3);
	entities.push_back(redBall);

	//Orange Room
	Item* flowerPot = new Item("Flower Pot", "A simple ceramic flower pot, full of fertile soil.", orangeRoom, ItemType::COMMON);
	Item* bucket = new Item("Bucket", "A wooden bucket full of water.", orangeRoom, ItemType::COMMON);
	Item* water = new Item("Water", "Some water", bucket, ItemType::COMMON, false, false, false, true);
	Item* orangeTable = new Item("Orange Table", "A wooden old table, standing in the middle of the room.", orangeRoom, ItemType::COMMON);
	Item* appleSeeds = new Item("Apple Seeds", "A few apple seeds.", orangeTable, ItemType::COMMON, false, false, false, true);
	Item* orangeSeeds = new Item("Orange Seeds", "A few orange seeds.", orangeTable, ItemType::COMMON, false, false, false, true);
	Item* strawberrySeeds = new Item("Strawberry Seeds", "A few strawberry seeds.", orangeTable, ItemType::COMMON, false, false, false, true);
	Item* orange = new Item("Orange", "A fresh orange. Seems like something is glowing inside.", flowerPot, ItemType::COMMON, false, false, true, true);
	Item* yellowKey = new Item("Yellow Key", "A small yellow key. It was stored inside the orange.", orange, ItemType::KEY, false, true, false, true);
	Item* orangeBall = new Item("Orange Ball", "A ball of condensed orange light", orange, ItemType::LIGHTBALL, false, true, false, true);

	entities.push_back(flowerPot);
	entities.push_back(bucket);
	entities.push_back(water);
	entities.push_back(orangeTable);
	entities.push_back(appleSeeds);
	entities.push_back(orangeSeeds);
	entities.push_back(strawberrySeeds);
	entities.push_back(orange);
	entities.push_back(yellowKey);
	entities.push_back(orangeBall);

	//Yellow Room
	Item* yellowBall = new Item("Yellow Ball", "A ball of condensed yellow light", yellowRoom, ItemType::LIGHTBALL, false, false, true, true);	
	Item* greenKey = new Item("Green Key", "A small green key", yellowRoom, ItemType::KEY, false, false, true, true);

	entities.push_back(yellowBall);
	entities.push_back(greenKey);

	//Green Room
	Item* Crocodile = new Item("Emerald Crocodile", "A magnificent Crocodile carved in emerald. It has its jaws wide open, as if it "
		"was expecting something.", greenRoom, ItemType::COMMON);
	Item* cabinet = new Item("Cabinet", "A wooden cabinet. No lock can be seen", greenRoom, ItemType::COMMON);
	Item* meatPiece = new Item("Meat", "A piece of fresh meat.", cabinet, ItemType::COMMON, false, true, false, true);
	Item* greenBall = new Item("Green Ball", "A ball of condensed green light", greenRoom, ItemType::LIGHTBALL, false, false, true, true);
	Item* blueKey = new Item("Blue Key", "A small blue key", greenRoom, ItemType::KEY, false, false, true, true);

	entities.push_back(Crocodile);
	entities.push_back(cabinet);
	entities.push_back(meatPiece);
	entities.push_back(greenBall);
	entities.push_back(blueKey);

	//Blue Room
	Item* leftStatue = new Item("Left Statue", "Huge statue made of stone. It's looking down happily to the items below it.", blueRoom,
		ItemType::COMMON);
	Item* rightStatue = new Item("Right Statue", "Huge statue made of stone. It's looking to the left, with a hint of envy on its expression.", blueRoom,
		ItemType::COMMON);
	Item* goldPiece = new Item("Gold", "Gold piece, shining brightly.", leftStatue, ItemType::COMMON, false, false, false, true);
	Item* silverPiece = new Item("Silver", "Silver piece, shining brightly.", leftStatue, ItemType::COMMON, false, false, false, true);
	Item* bronzePiece = new Item("Bronze", "Bronze piece, shining brightly.", leftStatue, ItemType::COMMON, false, false, false, true);
	Item* tear = new Item("Tear", "Tear of water, a bright light is coming from inside", leftStatue, ItemType::COMMON, false, false, true, true);
	Item* violetKey = new Item("Violet Key", "A small violet key", tear, ItemType::KEY, false, true, false, true);
	Item* blueBall = new Item("Blue Ball", "A ball of condensed blue light", tear, ItemType::LIGHTBALL, false, true, false, true);

	entities.push_back(leftStatue);
	entities.push_back(rightStatue);
	entities.push_back(goldPiece);
	entities.push_back(silverPiece);
	entities.push_back(bronzePiece);
	entities.push_back(tear);
	entities.push_back(violetKey);
	entities.push_back(blueBall);

	//Violet Room
	Item* violetChest = new Item("Violet Chest", "A wooden chest painted violet, no lock can be seen. A number one is painted on top", 
		violetRoom, ItemType::COMMON);
	//Depth one
	Item* box2 = new Item("Box 2", "A small box with the number 2 painted on the top", violetChest, ItemType::COMMON, false, true);
	Item* box3 = new Item("Box 3", "A small box with the number 3 painted on the top", violetChest, ItemType::COMMON, false, true);
	//Depth two
	//box1
	Item* box4 = new Item("Box 4", "A small box with the number 4 painted on the top", box3, ItemType::COMMON, false, true);
	Item* box5 = new Item("Box 5", "A small box with the number 5 painted on the top", box3, ItemType::COMMON, false, true);
	Item* box6 = new Item("Box 6", "A small box with the number 6 painted on the top", box3, ItemType::COMMON, false, true);
	//box2
	Item* box7 = new Item("Box 7", "A small box with the number 7 painted on the top", box2, ItemType::COMMON, false, true);
	Item* box8 = new Item("Box 8", "A small box with the number 8 painted on the top", box2, ItemType::COMMON, false, true);
	Item* box9 = new Item("Box 9", "A small box with the number 9 painted on the top", box2, ItemType::COMMON, false, true);
	//Depth three
	Item* box10 = new Item("Box 10", "A small box with the number 10 painted on the top", box6, ItemType::COMMON, false, true);
	Item* box11 = new Item("Box 11", "A small box with the number 11 painted on the top", box4, ItemType::COMMON, false, true);
	Item* box12 = new Item("Box 12", "A small box with the number 12 painted on the top", box5, ItemType::COMMON, false, true);
	Item* box13 = new Item("Box 13", "A small box with the number 13 painted on the top", box7, ItemType::COMMON, false, true);
	Item* box14 = new Item("Box 14", "A small box with the number 14 painted on the top", box8, ItemType::COMMON, false, true);
	Item* box15 = new Item("Box 15", "A small box with the number 15 painted on the top", box9, ItemType::COMMON, false, true);

	Item* violetBall = new Item("Violet Ball", "A ball of condensed violet light", box10, ItemType::LIGHTBALL, false, true, false, true);

	entities.push_back(violetChest);
	entities.push_back(box2);
	entities.push_back(box3);
	entities.push_back(box4);
	entities.push_back(box5);
	entities.push_back(box6);
	entities.push_back(box7);
	entities.push_back(box8);
	entities.push_back(box9);
	entities.push_back(box10);
	entities.push_back(box11);
	entities.push_back(box12);
	entities.push_back(box13);
	entities.push_back(box14);
	entities.push_back(box15);
	entities.push_back(violetBall);

	//Exits
	Exit* ex1 = new Exit("North", "South", "Light Door, locked. Looks like you need some kind of key.", redRoom, orangeRoom, false, true, orangeKey2);
	Exit* ex2 = new Exit("South", "North", "Light Door, locked. Looks like you need some kind of ball.", redRoom, yellowRoom, false, true, yellowKey);
	Exit* ex3 = new Exit("West", "East", "Narrow Passage", centerRoom, redRoom);
	Exit* ex4 = new Exit("South", "North", "Narrow Passage", corpseRoom, centerRoom, true);
	Exit* ex5 = new Exit("South", "North", "Light Door, locked. Looks like you need some kind of ball.", centerRoom, godRoom, false, true, whiteBall);
	Exit* ex6 = new Exit("East", "West", "Light Door, locked. Looks like you need some kind of ball.", centerRoom, greenRoom, false, true, greenKey);
	Exit* ex7 = new Exit("North", "South", "Light Door, locked. Looks like you need some kind of ball.", greenRoom, blueRoom, false, true, blueKey);
	Exit* ex8 = new Exit("South", "North", "Light Door, locked. Looks like you need some kind of ball.", greenRoom, violetRoom, false, true, violetKey);

	entities.push_back(ex1);
	entities.push_back(ex2);
	entities.push_back(ex3);
	entities.push_back(ex4);
	entities.push_back(ex5);
	entities.push_back(ex6);
	entities.push_back(ex7);
	entities.push_back(ex8);

	//Player
	player = new Player("Light corpse", "You are a floating smoke-like creature, with a small light flickering inside you.", corpseRoom);

	entities.push_back(player);

	//NPC God
	god = new NPC("Light God", "You see a flowing creature emanating light towards all directions. Your flickering light seems "
		"synced with the creature's.", godRoom, "\nThe light inside you flickers, you feel a small pull inside, urging you to hurry.\nYou hear a "
		"whispering sound coming through the light, \"Hurry, you must bring me the light...\"", "You inch closer to the creature, touching it "
		"eventually. When you touch it you feel you body filling up, the once flickering, weak light inside you now gleams with intensity. "
		"Then it starts to transfer to the creature, which howls with joy. After a while, all light has been transferred, your inner light "
		"flicks one last time as you fade into darkness...");

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
		else if (Same(args[0], "inventory"))
		{
			player->Inventory();
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
		else if (Same(args[0], "open"))
		{
			player->Open(args);
		}
		else if (Same(args[0], "take"))
		{
			player->Take(args);
		}
		else if (Same(args[0], "drop"))
		{
			player->Drop(args);
		}
		else
		{
			ret = false;
		}
		break;
	case 3:
		if (Same(args[0], "look"))
		{
			player->Look(args);
		}
		else if (Same(args[0], "open"))
		{
			player->Open(args);
		}
		else if (Same(args[0], "take"))
		{
			player->Take(args);
		}
		else if (Same(args[0], "drop"))
		{
			player->Drop(args);
		}
		else if (Same(args[0], "touch"))
		{
			player->Touch(args);
			if (Same(args[1], "light") && Same(args[2], "god"))
				end = true;
		}
		else
		{
			ret = false;
		}
		break;
	case 4:
		if (Same(args[0], "open"))
		{
			player->Open(args);
		}
		else if (Same(args[0], "unlock"))
		{
			player->Unlock(args);
		}
		else if (Same(args[0], "drop"))
		{
			player->Drop(args);
		}
		else
		{
			ret = false;
		}
		break;
	case 5:
		if (Same(args[0], "open"))
		{
			player->Open(args);
		}
		else if (Same(args[0], "unlock"))
		{
			player->Unlock(args);
		}
		else if (Same(args[0], "drop"))
		{
			player->Drop(args);
		}
		else
		{
			ret = false;
		}
		break;
	case 6:
		if (Same(args[0], "open"))
		{
			player->Open(args);
		}
		else if (Same(args[0], "drop"))
		{
			player->Drop(args);
		}
		else
		{
			ret = false;
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

	//Sentence spoken by the god to urge the player to finish quickly
	if ((now - tickTimerCreature) / CLOCKS_PER_SEC > STATE_CREATURE_TICK_FREQUENCY)
	{
		for (vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
			if ((*it)->type == EntityType::NPC)
				(*it)->Tick();

		tickTimerCreature = now;
	}

	//Timer to restart game if player has not finished it
	if ((now - tickTimerEnd) / CLOCKS_PER_SEC > STATE_END_LIFE_FREQUENCY)
	{
		restart = true;
	}

	//Timer to check state of items and act in consequence
	if ((now - tickTimerItem) / CLOCKS_PER_SEC > STATE_ITEM_TICK_FREQUENCY)
	{
		for (vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
			if ((*it)->type == EntityType::ITEM)
				(*it)->Tick();

		tickTimerItem = now;
	}

	//Timer to check the location of the player
	if ((now - tickTimerLocation) / CLOCKS_PER_SEC > STATE_LOCATION_TICK_FREQUENCY)
	{
		for (vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
			if ((*it)->type == EntityType::PLAYER)
				(*it)->Tick();

		tickTimerLocation = now;
	}
}


