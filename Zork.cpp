
#include <iostream>
#include <string>
#include <vector>
#include "World.h"
#include <conio.h>
#include <stdio.h>
#include <sstream>
using namespace std;

#define INPUT_ "\033[1;36m"
#define BOLD_ "\033[1;4;33m"
#define _RESTART "\033[0m"

#ifdef _WIN32
#include <windows.h>

#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#define DISABLE_NEWLINE_AUTO_RETURN  0x0008

void activateVirtualTerminal()
{
	HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD consoleMode;
	GetConsoleMode(handleOut, &consoleMode);
	consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	consoleMode |= DISABLE_NEWLINE_AUTO_RETURN;
	SetConsoleMode(handleOut, consoleMode);
}
#endif

vector<string> ignoredWords = { "Into","On","To","Through","In","The","With" };
World game;

bool isIgnoredWord(string word) {

	for (string ignoredWord : ignoredWords) {
		if (word == ignoredWord) return true;
	}
	return false;
}

void ParseAction(vector<string> inputPlayer) {
	cout << _RESTART "----------------------------------------------" << endl;
	game.ParseAction(inputPlayer);
	cout << "----------------------------------------------" INPUT_ << endl;
}

void GameLoop() {
	vector<string> inputPlayer;

	while (true)
	{
		inputPlayer.clear();

		string readInput;
		getline(cin, readInput);
		stringstream fullInput(readInput);
		string oneWord;

		while (getline(fullInput, oneWord, ' '))
		{
			oneWord[0] = toupper(oneWord[0]);
			for (int i = 1; i < (signed)oneWord.size(); i++)
			{
				oneWord[i] = tolower(oneWord[i]);
			}
			if (!isIgnoredWord(oneWord)) inputPlayer.push_back(oneWord);
		}

		ParseAction(inputPlayer);

		if (game.isFinish()) {
			break;
		}
	}
}

int main()
{
#ifdef _WIN32
	activateVirtualTerminal();
#endif

	cout << BOLD_ "WELCOME! The game is about to start" _RESTART << endl;
	game.ChargeData();
	game.Start();

	GameLoop();
	cout << BOLD_ "THANKS FOR PLAYING" _RESTART << endl;
	system("pause");
}