#include <string>
#include <vector>
#include <iostream>

#include <conio.h>

#include "Globals.h"

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
		}
	}

	return 0;
}