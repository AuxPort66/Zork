#pragma once
#include "World.h"
using namespace std;




void World::Start() {
	Room* initialroom = new Room("Hab1", "Una habitación normal y corriente, tiene una puerta", NULL);
	Room* secondroom = new Room("Hab2", "Una habitación menos normal y corriente, tiene una puerta", NULL);

	Exits* exits = new Exits("Door", "Door between Hab1 and Hab2", initialroom, secondroom, "Usaste la puerta, hizo algo de ruido pero nada preocupante");

	actualRoom = initialroom;

	Look("Room");
}

void World::ParseAction(vector<string> args) {

	if (args[0] == "Go") {
		Go(args[1]);
	}
	else if (args[0] == "Look") {
		if (args.size() == 1) Look("Room");
		else Look(args[1]);
	}
}

void World::Look(string name) {

	if (name == "Room") {
		cout << "Miras a tu alrededor, estas en:" << endl;
		PrintRoom(actualRoom);
	}
	else {

		Entity* target = actualRoom->CheckifContains(name);

		if (target != NULL) {
			cout << target->GetDescription() << endl;
		}
		else
		{
			cout << "The what?" << endl;
		}
	}
}

void World::Go(string name) {

	Exits* exit = (Exits*)actualRoom->CheckifContains(name);

	if (exit != NULL && exit->type == EXIT) {

		actualRoom = exit->GetDestination(actualRoom);

		cout << exit->GetGoActionDescription() << " Acabaste en:" << endl;
		PrintRoom(actualRoom);
	}
	else
	{
		cout << "The what?" << endl;
	}
}

void World::PrintRoom(Room* room) {
	cout << room->GetName() << endl;
	cout << room->GetDescription() << endl;
}

