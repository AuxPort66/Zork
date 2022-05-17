#pragma once
#include "World.h"
using namespace std;

void World::Start() {


	Room* initialroom = new Room("Hab1", "Una habitación normal y corriente, tiene una puerta", NULL);
	Room* secondroom = new Room("Hab2", "Una habitación menos normal y corriente, tiene una puerta", NULL);

	Exits* exits = new Exits("Door", "Door between Hab1 and Hab2", initialroom, secondroom,"Usaste la puerta, hizo algo de ruido pero nada preocupante");
	exits->lock = true;


	Item* item = new Item("Piedra", "Es una piedra, parece perfecta para rebotar en el lago si sabes lanzarla", initialroom, "Tomas la piedra y la pones en el bolsillo", "Usas la piedra, pero no sabes bien como");
	Item* item2 = new Item("Piedra2", "Es una piedra dentro de una piedra, parece perfecta para rebotar en el lago si sabes lanzarla", item, "Tomas la piedra dentro de una piedra y la pones en el bolsillo", "Usas la piedra, pero no sabes bien como");
	item2->accesibleContent = false;

	ItemActions* action = new ItemActions((Entity*)item2, true);
	ItemActions* action2 = new ItemActions(exits, true);
	item2->AddAction(action);
	item2->AddAction(action2);
	
	Item* item3 = new Item("Piedra3", "Es una piedra dentro de una piedra dentro de una piedra, parece perfecta para rebotar en el lago si sabes lanzarla", item2, "Tomas la piedra dentro de una piedra dentro de una piedra y la pones en el bolsillo", "Usas la piedra, pero no sabes bien como");
		
	actualRoom = initialroom;

	player = new Player("Blake", "A person, I guess", actualRoom);
	player->ChangeStat(PERCEPTION, 1);
	player->ChangeStat(STRENGHT, 2);
	player->ChangeStat(DEFENSE, 3);


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
	else if (args[0] == "Use") {
		if (args.size() == 2) Use(args[1],"");
		else cout << "Use what? that? or that? Or that other thing? Which?!" << endl;
	}
	else if (args[0] == "Inventory") {
		if (player->Getcontent().size() > 0) Inventory(player);
		else cout << "You have fewer things than me, which is already saying a lot considering that I am just a text without a body" << endl;
	}
}

void World::Use(string nameObjectUsed, string nameObjectUsedOn) {
	if (nameObjectUsedOn == "") {
		Item* itemUsed = (Item*)actualRoom->CheckifContains(nameObjectUsed);
		if (itemUsed != NULL) {
			if (itemUsed->type == EXITS) Go(nameObjectUsed);
			else if (itemUsed->type == ITEM) {
				itemUsed->UseItem();
			}
			else {
				cout << "Can you explain to me how you will use that, exactly?" << endl;
			}
		}
		Item* itemUsed = (Item*)player->CheckifContains(nameObjectUsed);
		if (itemUsed != NULL) {
			if (itemUsed->type == ITEM) {
				itemUsed->UseItem();
			}
			else
			{
				cout << "Can you explain to me how you will use that, exactly?" << endl;
			}
		}
		else
		{
			cout << "Use what?" << endl;
		}
	}
}

void World::Look(string name) {

	if (name == "Room") {
		cout << "Look around you, you're in:" << endl;
		PrintRoom(actualRoom);
	}
	else if (name == "Me") {
		cout << "Look at yourself: " << endl;
		cout << player->GetName() << endl;
		cout << player->GetDescription() << endl;
		PrintStats(player);
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

		if (exit->type == EXITS) {
			if (!exit->lock) {
				actualRoom = exit->GetDestination(actualRoom);

				cout << exit->GetGoActionDescription() << " You ended up at:" << endl;
				PrintRoom(actualRoom);
			}
			else
			{
				cout << "It's closed" << endl;
			}
			
		}
		else
		{
			cout << "I don't think it's used like that..." << endl;
		}

	}
	else
	{
		cout << "Go where? I don't see that here" << endl;
	}
}

void World::Pick(string name) {

	Item* item = (Item*)actualRoom->CheckifContains(name);

	if (item != NULL) {

		if (item->type == ITEM && item->pickable) {
			cout << item->GetPickupActionDescription() << endl;
			item->GetParent()->RemoveChild(item);
			player->AddChild(item);
		}
		else
		{
			cout << "It doesn't seem like you can grab that, although your stubbornness doesn't stop you from trying again later." << endl;
		}
	}
	else
	{
		cout << "Take what? I don't see that here" << endl;
	}
}

void World::Drop(string name) {

	Item* item = (Item*)player->CheckifContains(name);
	if (item != NULL) {
		if (item->dropable) {
			cout << "Drop " << item->name << endl;
			item->GetParent()->RemoveChild(item);
			actualRoom->AddChild(item);
		}
		else
		{
			cout << "Nah, you won't throw that away" << endl;
		}
	}
	else
	{
		cout << "How are you going to throw away something you don't have? Are you ok?" << endl;
	}

}


void World::Inventory(Entity* inventory) {
	list<Entity*> content = inventory->Getcontent();
	if (content.size() > 0) {
		for (Entity* child : content) {
			cout << child->name << endl;
			if (child->accesibleContent)Inventory(child);
		}
	}
}

void World::PrintRoom(Room* room) {
	cout << room->GetName() << endl;
	cout << room->GetDescription() << endl;
}

void World::PrintStats(Creature* creature) {
	cout << "HP: " << creature->hp << endl;
	cout << "STRONG: " << creature->strenght << endl;
	cout << "PERCEPTION: " << creature->perception << endl;
	cout << "DEFENSE: " << creature->defense << endl;
}
