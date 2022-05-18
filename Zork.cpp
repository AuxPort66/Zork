// Zork.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include <vector>
#include "World.h"
#include <conio.h>
#include <stdio.h>
#include <sstream>

using namespace std;

int main()
{
    World game;
	game.Start();
	vector<string> args;

	while (true)
	{
		if (_kbhit()) {

			string read;

			getline(cin, read);
			stringstream action(read);
			string tmp;
			args.clear();
			while (getline(action, tmp,' '))
			{
				tmp[0] = toupper(tmp[0]);
				for (int i = 1; i < tmp.size(); i++)
				{
					tmp[i] = tolower(tmp[i]);
				}
				if (tmp != "Into" && tmp != "On" && tmp != "To" && tmp != "Through" && tmp != "In" && tmp != "The") args.push_back(tmp);
			}
			game.ParseAction(args);
		}
	}

}
