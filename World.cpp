#pragma once
#include "World.h"
using namespace std;

void World::Start() {


	Room* initialroom = new Room("Hab1", "Una habitación normal y corriente, tiene una puerta", NULL);
	Room* secondroom = new Room("Hab2", "Una habitación menos normal y corriente, tiene una puerta", NULL);

	Exits* exits = new Exits("Door", "Door between Hab1 and Hab2", initialroom, secondroom,"Usaste la puerta, hizo algo de ruido pero nada preocupante");
	exits->lock = true;


	Item* item = new Item("Piedra", "Es una piedra, parece perfecta para rebotar en el lago si sabes lanzarla", initialroom, "Tomas la piedra y la pones en el bolsillo");
	Item* item2 = new Item("Piedra2", "Es una piedra dentro de una piedra, parece perfecta para rebotar en el lago si sabes lanzarla", item, "Tomas la piedra dentro de una piedra y la pones en el bolsillo");
	item2->accesibleContent = false;
	item2->lostOnUse = true;

	ItemConsecuences* action = new ItemConsecuences((Entity*)item2, true);
	Action* actionswhenUse = new Action(NULL, "Usaste la piedra2, no se como, pero eso hizo que se oyerá un click en ella");
	actionswhenUse->Addconsecuence(action);

	Action* actionswhenUseOnDoor = new Action(exits, "Usaste la piedra2 en la puerta, no se como la verdad, pero escuchaste un click");
	ItemConsecuences* action2 = new ItemConsecuences(exits, true);
	actionswhenUseOnDoor->Addconsecuence(action2);

	item2->AddAction(actionswhenUse);
	item2->AddAction(actionswhenUseOnDoor);
	
	Item* item3 = new Item("Piedra3", "Es una piedra dentro de una piedra dentro de una piedra, parece perfecta para rebotar en el lago si sabes lanzarla", item2, "Tomas la piedra dentro de una piedra dentro de una piedra y la pones en el bolsillo");
		
	actualRoom = initialroom;

	player = new Player("Blake", "A person, I guess", actualRoom);
	player->ChangeStat(PERCEPTION, 1);
	player->ChangeStat(STRENGHT, 2);
	player->ChangeStat(DEFENSE, 3);


	Examine("Room");
}



void World::ParseAction(vector<string> args) {

	if (args[0] == "Go") {
		if (args.size() > 2) cout << "Ok, that was confusing. Decide, Go where?" << endl;
		else if (args.size() == 2) Go(args[1]);
		else cout << "Go? Where? Dumb dumb" << endl;
	}
	else if (args[0] == "Examine" || args[0] == "Look") {
		if (args.size() == 1) Examine("Room");
		else if (args.size() > 2) cout << "You have two eyes but I don't think you can examine two things at the same time." << endl;
		else Examine(args[1]);
	}
	else if (args[0] == "Pick" || args[0] == "Take") {
		if (args.size() > 2) cout << "Ok, that was confusing. Decide, Pick what?" << endl;
		else if (args.size() == 2) Pick(args[1]);
		else cout << "Pick? What? Me?" << endl;
	}
	else if (args[0] == "Drop") {
		if(args.size() > 3) cout << "Ok, that was confusing. Decide, Drop what?" << endl;
		else if (args.size() == 3) Drop(args[1], args[2]);
		else if (args.size() == 2) Drop(args[1],"");
		else cout << "Drop? What? You?" << endl;
	}
	else if (args[0] == "Put") {
		if (args.size() > 3) cout << "Ok, that was confusing. Decide, Put what on where?" << endl;
		else if (args.size() == 3) Drop(args[1], args[2]);
		else cout << "Put? What? on Where?" << endl;
	}
	else if (args[0] == "Use") {
		if (args.size() > 2) Use(args[1], args[2]);
		else if (args.size() == 2) Use(args[1],"");
		else cout << "Use what? that? or that? Or that other thing? Which?!" << endl;
	}
	else if (args[0] == "Inventory") {
		if (player->Getcontent().size() > 0) Inventory(player);
		else cout << "You have fewer things than me, which is already saying a lot considering that I am just a text without a body" << endl;
	}
}

void World::Use(string nameObjectUsed, string nameObjectUsedOn) {

	Item* itemUsed = (Item*)actualRoom->CheckifContains(nameObjectUsed);
	if(itemUsed == NULL) itemUsed = (Item*)player->CheckifContains(nameObjectUsed);
	
	if (itemUsed != NULL) {
		if (nameObjectUsed == nameObjectUsedOn) cout << "No. Just...No. You can't do that" << endl;
		else {
			if (itemUsed->type == EXITS && nameObjectUsedOn == "") Go(nameObjectUsed);
			else if (itemUsed->type == ITEM) {

				if (nameObjectUsedOn == "") itemUsed->UseItem(NULL);
				else {
					Item* itemUsedOn = (Item*)actualRoom->CheckifContains(nameObjectUsedOn);
					if (itemUsedOn == NULL) itemUsedOn = (Item*)player->CheckifContains(nameObjectUsedOn);

					if (itemUsedOn != NULL) {
						itemUsed->UseItem(itemUsedOn);
					}
					else
					{
						cout << "You want to use that on what?" << endl;
					}

				}

			}
			else {
				cout << "Can you explain to me how you will use that, exactly?" << endl;
			}
		}
	}
	else {
		cout << "Use what?" << endl;
	}
}

void World::Examine(string name) {

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
			Entity* target = player->CheckifContains(name);

			if (target != NULL) {
				cout << target->GetDescription() << endl;
			}
			else
			{
				cout << "The what? You don't have that. Look again your Inventory." << endl;
			}
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

void World::Drop(string dropped, string container ) {

	if (dropped == container) cout << "No. Just...No. You can't do that" << endl;
	else {
		Item* itemDropped = (Item*)player->CheckifContains(dropped);
		if (itemDropped != NULL) {

			if (itemDropped->dropable) {
				if (container == "") {
					cout << "Drop " << itemDropped->name << endl;
					itemDropped->GetParent()->RemoveChild(itemDropped);
					actualRoom->AddChild(itemDropped);
				}
				else {
					Item* itemContainer = (Item*)actualRoom->CheckifContains(container);
					if (itemContainer == NULL) Item* itemContainer = (Item*)player->CheckifContains(container);
					if (itemContainer != NULL) {
						if (itemContainer->accesibleContent) {
							cout << "Drop " << itemDropped->name << "on" << itemContainer->name << endl;
							itemDropped->GetParent()->RemoveChild(itemDropped);
							itemContainer->AddChild(itemDropped);
						}
						else
						{
							cout << "You can put things there" << endl;
						}
					}
					else
					{
						cout << "Where you want to drop that? Excuse me?" << endl;
					}
				}
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
