#include <string>
#include <vector>
#include <iostream>

#include <conio.h>

#include "Globals.h"
#include "World.h"

#define BACKSPACE '\b'
#define RETURN '\r'
#define BLANK ' ';

using namespace std;

int main()
{
	char key;
	string playerInput;
	vector<string> inputArgs;
	inputArgs.reserve(10);

	bool play = true;

	cout << "Welcome to Light and Darkness!" << endl;

	cout << "> ";

	World* world = new World();

	inputArgs.push_back("look");

	while (play)
	{
		if (_kbhit() != 0)
		{
			key = _getch();

			if (key == BACKSPACE)
			{
				if (playerInput.length() > 0)
				{
					playerInput.pop_back();
					cout << BACKSPACE;
					cout << BLANK;
					cout << BACKSPACE;
				}
			}
			else if (key != RETURN)
			{
				playerInput += key;
				cout << key;
			}
			else
			{
				Tokenize(playerInput, inputArgs);
			}
		}

		if (inputArgs.size() > 0 && Same(inputArgs[0], "quit"))
			break;

		if (world->Tick(inputArgs) == false)
			cout << "\nSorry, I don't understand your command." << endl;

		if (inputArgs.size() > 0)
		{
			inputArgs.clear();
			playerInput = "";
			cout << "\n> ";
		}

		if (world->restart == true)
		{
			cout << "\nThe light inside flickers pathetically one last time, and slowly you feel your conscience drifting away. As you close your eyes you hear "
				"an angry scream: \"You fool! I require your light to survive, you must deliver it next time...\"\n\n" << endl;
			
			delete world;
			world = nullptr;
			world = new World();

			cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
			cout << "> ";

			inputArgs.push_back("look");
		}

		if (world->end)
		{
			cout << "\n\n-------------------------------\nCongratulations! You finished the game!" << endl;
			play = false;
		}

	}

	return 0;
}