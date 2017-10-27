#include <iostream>

#include "Item.h"
#include "Globals.h"

using namespace std;

Item::Item(const char * name, const char * description, Entity * parent, ItemType itemType, bool locked, bool openToSee, bool notVisible, bool takeable, Entity* key) :
	Entity(name, description, parent), itemType(itemType), contentsLocked(locked), openToSee(openToSee), notVisible(notVisible), takeable(takeable), key(key)
{
	type = EntityType::ITEM;
}

Item::~Item()
{
}

void Item::Look() const
{
	cout << "\n---------------" << endl;
	cout << name << endl;
	cout << "---------------" << endl;
	cout << description << "\n" << endl;

	list<Entity*> stuff;
	FindAll(EntityType::ITEM, stuff);

	if (stuff.size() > 0)
	{
		if (contentsLocked == true)
		{
			cout << "This item is locked." << endl;
		}
		else
		{
			bool allNotVisible = true;
			bool someToOpen = false;

			for (list<Entity*>::const_iterator it = stuff.begin(); it != stuff.end(); ++it)
			{
				Item* item = (Item*)*it;
				if (item->openToSee == false)
				{
					if (item->notVisible == false)
					{
						allNotVisible = false;
						cout << "This item contains " << (*it)->name << endl;
					}
				}
				else
				{
					someToOpen = true;
				}
			}
			if (someToOpen == true)
			{
				cout << "This item contains something. Open it to see its contents." << endl;
			}
			else if (allNotVisible == true)
			{
				cout << "This item does not contain anything." << endl;
			}
		}
	}
	else
	{
		cout << "This item does not contain anything." << endl;
	}
}

void Item::Tick()
{
	if (Same(name, "Flower Pot"))
	{
		bool orangeSeeds = false;
		bool water = false;
		vector<Entity*>::const_iterator waterIterator = container.end();
		vector<Entity*>::const_iterator orangeSeedsIterator = container.end();
		vector<Entity*>::const_iterator orangeIterator = container.end();

		for (vector<Entity*>::const_iterator it = container.begin(); it != container.cend(); ++it)
		{
			Item* item = (Item*)*it;
			if (Same(item->name, "Orange Seeds"))
			{
				orangeSeeds = true;
				orangeSeedsIterator = it;
			}
			else if (Same(item->name, "Water"))
			{
				water = true;
				waterIterator = it;
			}
			else if (Same(item->name, "Orange"))
			{
				orangeIterator = it;
			}
		}

		if (orangeIterator != container.end())
		{
			Item* orange = (Item*)*orangeIterator;

			if (orange->notVisible == true)
			{
				if (orangeSeeds == true && water == true)
				{
					cout << "\nThe water, the seeds and the soil magically merge together and a beautiful but tiny orange tree grows. One single orange "
						"surrounded by green leaves stares at you." << endl;

					orange->notVisible = false;

					Item* orangeSeeds = (Item*)*orangeSeedsIterator;
					Item* water = (Item*)*waterIterator;

					orangeSeeds->notVisible = true;
					water->notVisible = true;

					cout << "\n> ";
				}
			}
		}
	}
	if (Same(name, "Emerald Crocodile"))
	{
		bool fed = false;

		for (vector<Entity*>::const_iterator it = container.begin(); it != container.cend(); ++it)
		{
			Item* item = (Item*)*it;
			if (Same(item->name, "Meat"))
			{
				fed = true;
				item->notVisible = true;
			}
		}

		if (fed == true)
		{
			Item* item = (Item*)parent->Find("Green Ball", EntityType::ITEM);
			if (item != nullptr)
			{
				if (item->notVisible == true)
				{
					cout << "\nThe Crocodile, thankful for its meal, glows briefly. Two objects, invisible before, now appear in the room." << endl;

					item->notVisible = false;
					item = (Item*)parent->Find("Blue Key", EntityType::ITEM);
					if (item != nullptr)
						item->notVisible = false;

					cout << "\n> ";
				}
			}
		}
	}
	if (Same(name, "Left Statue"))
	{
		if (container.size() == 1) //Just the hidden tear
		{
			description = "Huge statue made of stone. It's looking down with a concerned expression.";
		}

		Item* rightStatue = (Item*)parent->Find("Right Statue", EntityType::ITEM);
		if (rightStatue != nullptr)
		{
			if (rightStatue->container.size() == 3)
			{
				rightStatue->description = "Huge statue made of stone. It's looking to the left with a smirk on his face";

				Item* item = (Item*)Find("Tear", EntityType::ITEM);
				if (item != nullptr)
				{
					if (item->notVisible == true)
					{
						cout << "\nThe Left Statue has lost all his belongings to the Right Statue. Something is coming out from his eye." << endl;
						item->notVisible = false;

						cout << "\n> ";
					}
				}
			}
		}
	}
	if (Same(name, "Stone Pillar"))
	{
		Item* whiteBall = (Item*)parent->Find("White Ball", EntityType::ITEM);

		if (whiteBall != nullptr)
		{
			if (whiteBall->notVisible == true)
			{
				bool colorsInPlace = true;

				//First Hole
				Item* item = (Item*)container.at(0);
				if (item != nullptr)
				{
					if (item->container.size() == 1)
					{
						Item* ball = (Item*)item->container.at(0);
						if (ball != nullptr)
						{
							if (Same(ball->name, "Red Ball") == false)
							{
								colorsInPlace = false;
							}
						}
					}
					else
					{
						colorsInPlace = false;
					}
				}

				//Second Hole
				if (colorsInPlace)
				{
					item = (Item*)container.at(1);
					if (item != nullptr)
					{
						if (item->container.size() == 1)
						{
							Item* ball = (Item*)item->container.at(0);
							if (ball != nullptr)
							{
								if (Same(ball->name, "Orange Ball") == false)
								{
									colorsInPlace = false;
								}
							}
						}
						else
						{
							colorsInPlace = false;
						}
					}
				}

				//Third Hole
				if (colorsInPlace)
				{
					item = (Item*)container.at(2);
					if (item != nullptr)
					{
						if (item->container.size() == 1)
						{
							Item* ball = (Item*)item->container.at(0);
							if (ball != nullptr)
							{
								if (Same(ball->name, "Yellow Ball") == false)
								{
									colorsInPlace = false;
								}
							}
						}
						else
						{
							colorsInPlace = false;
						}
					}
				}

				//Fourth Hole
				if (colorsInPlace)
				{
					item = (Item*)container.at(3);
					if (item != nullptr)
					{
						if (item->container.size() == 1)
						{
							Item* ball = (Item*)item->container.at(0);
							if (ball != nullptr)
							{
								if (Same(ball->name, "Green Ball") == false)
								{
									colorsInPlace = false;
								}
							}
						}
						else
						{
							colorsInPlace = false;
						}
					}
				}

				//Fifth Hole
				if (colorsInPlace)
				{
					item = (Item*)container.at(4);
					if (item != nullptr)
					{
						if (item->container.size() == 1)
						{
							Item* ball = (Item*)item->container.at(0);
							if (ball != nullptr)
							{
								if (Same(ball->name, "Blue Ball") == false)
								{
									colorsInPlace = false;
								}
							}
						}
						else
						{
							colorsInPlace = false;
						}
					}
				}

				//Sixth Hole
				if (colorsInPlace)
				{
					item = (Item*)container.at(5);
					if (item != nullptr)
					{
						if (item->container.size() == 1)
						{
							Item* ball = (Item*)item->container.at(0);
							if (ball != nullptr)
							{
								if (Same(ball->name, "Violet Ball") == false)
								{
									colorsInPlace = false;
								}
							}
						}
						else
						{
							colorsInPlace = false;
						}
					}
				}

				if (colorsInPlace)
				{
					cout << "\nAll the holes from the stone pillar shine brighly, all the colors collapsing onto each other. The intensity of the light "
						"keeps growing stronger, until finally it explodes and leaves a small object behind." << endl;

					whiteBall->notVisible = false;

					cout << "\n> ";
				}
			}
		}
	}
}

