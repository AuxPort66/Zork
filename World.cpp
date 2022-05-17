#pragma once
#include "World.h"
using namespace std;


list<Item*> inventory;


void World::Start() {
	Room* initialroom = new Room("Hab1", "Una habitación normal y corriente, tiene una puerta", NULL);
	Room* secondroom = new Room("Hab2", "Una habitación menos normal y corriente, tiene una puerta", NULL);

	Exits* exits = new Exits("Door", "Door between Hab1 and Hab2", initialroom, secondroom, "Usaste la puerta, hizo algo de ruido pero nada preocupante");

	Item* item = new Item("Piedra", "Es una piedra, parece perfecta para rebotar en el lago si sabes lanzarla", initialroom, "Tomas la piedra y la pones en el bolsillo", "Usas la piedra, pero no sabes bien como", true, true);

	actualRoom = initialroom;

	Look("Room");
}

void World::ParseAction(vector<string> args) {

	if (args[0] == "Go") {
		if (args.size() > 1) Go(args[1]);
		else cout << "Go where? Dumb dumb" << endl;
	}
	else if (args[0] == "Look") {
		if (args.size() == 1) Look("Room");
		else Look(args[1]);
	}
	else if (args[0] == "Pick" || args[0] == "Take") {
		if (args.size() > 1) Pick(args[1]);
		else cout << "Pick what? Me?" << endl;
	}
	else if (args[0] == "Drop") {
		if (args.size() > 1) Drop(args[1]);
		else cout << "Drop what? You?" << endl;
	}
	else if (args[0] == "Inventory") {
		Inventory();
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

	if (exit != NULL) {

		if (exit->type == EXIT) {
			actualRoom = exit->GetDestination(actualRoom);

			cout << exit->GetGoActionDescription() << " Acabaste en:" << endl;
			PrintRoom(actualRoom);
		}
		else
		{
			cout << "No creo que eso se use así..." << endl;
		}

	}
	else
	{
		cout << "Ir a donde? Yo no veo eso aqui" << endl;
	}
}

void World::Pick(string name) {

	Item* item = (Item*)actualRoom->CheckifContains(name);

	if (item != NULL) {

		if (item->type == ITEM && item->pickable) {
			cout << item->GetPickupActionDescription() << endl;
			inventory.push_back(item);
			actualRoom->RemoveChild(item);
		}
		else
		{
			cout << "No creo que puedas coger eso. Y si puedes no quiero verlo" << endl;
		}
	}
	else
	{
		cout << "Coger el que? Yo no veo eso aqui" << endl;
	}
}

void World::Drop(string name) {

	Item* item = isInInventory(name);
	if (item != NULL) {
		if (item->dropable) {
			cout << "Tiraste " << item->name << endl;
			actualRoom->AddChild(item);
			inventory.remove(item);
		}
		else
		{
			cout << "Nah, no vas a tirar eso" << endl;
		}
	}
	else
	{
		cout << "Como vas a tirar algo que ni tienes? Ya estas delirando?" << endl;
	}

}

Item* World::isInInventory(string name) {
	for (auto const& child : inventory) {
		if (child->name == name) return child;
	}
	return NULL;
}

void World::Inventory() {

	if (inventory.size() > 0) {
		for (auto const& child : inventory) {
			cout << child->name << endl;
		}
	}
	else
	{
		cout << "Tienes menos cosas que yo, que ya es mucho decir teniendo en cuenta que soy solo un texto sin cuerpo" << endl;
	}

}

void World::PrintRoom(Room* room) {
	cout << room->GetName() << endl;
	cout << room->GetDescription() << endl;
}

