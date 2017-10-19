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
	World world;

	bool play = true;

	cout << "Welcome to Light and Darkness!" << endl;

	cout << "> ";

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

		if (inputArgs.size() > 10 && Same(inputArgs[0], "quit"))
			break;

		if (inputArgs.size() > 0)
		{
			inputArgs.clear();
			playerInput = "";
			cout << "> ";
		}
	}

	return 0;
}