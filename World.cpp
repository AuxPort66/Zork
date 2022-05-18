#pragma once
#include "World.h"
#include <iomanip>
#include <iostream>
using namespace std;

#define INPUT_ "\033[1;36m"
#define BOLD_ "\033[1;33m"
#define _RESTART "\033[0m"

World::~World()
{
}

void World::Start()
{
	Examine("Room");
	cout << "----------------------------------------------" INPUT_ << endl;
}

void World::ChargeData() {


	Room* initialroom = new Room("Hab1", NULL, "Una habitación normal y corriente, tiene una puerta. Cuando examinas un poco mas ves que tiene un \033[1;33magujero\033[0m en una de las paredes");
	Room* secondroom = new Room("Hab2", NULL, "Una habitación menos normal y corriente, tiene una puerta");

	wholeExistance.push_back(initialroom);
	wholeExistance.push_back(secondroom);

	player = new Player("Blake", actualRoom, "A person, I guess");
	player->ChangeStat(Stats::PERCEPTION, 1);
	player->ChangeStat(Stats::STRENGHT, 2);
	player->ChangeStat(Stats::DEFENSE, 3);

	wholeExistance.push_back(player);


	Exits* exits = new Exits("Door", initialroom, secondroom, "Door between Hab1 and Hab2");
	exits->SetGoActionDescription("Usaste la puerta, hizo algo de ruido pero nada preocupante");
	exits->lock = true;

	wholeExistance.push_back(exits);

	Item* item = new Item("Agujero", initialroom,"Es un agujero, parece que puedes meter la mano por él pero no se si quieras... Ademas parece bastante profundo. Aunque al fondo creo que hay una especie de medallon");
	item->SetPickupActionDescription("Como vas a coger un agujero?");
	item->pickable = false;

	Item* item2 = new Item("Carne", initialroom,"Es un trozo de carne que sacaste de la nevera, lo unico que quedaba dentro la verdad");
	item2->SetPickupActionDescription("Coges el trozo de carne, está a medio telediario de ya no ser comestible pero quizas te sirve pa algo");
	item2->dropable = false;
	item2->lostOnUse = true;

	Item* item3 = new Item("Medallon", item,"Medallon triangular, parece contener algo dentro");
	item3->SetPickupActionDescription("No llegas al medallón, esta demasiado a dentro del agujero");
	item3->accesibleContent = false;
	item3->reachable = false;
	

	ItemConsecuences* action = new ItemConsecuences((Entity*)item3, true);
	action->reversible = false;
	Action* actionswhenUse = new Action(item3, "Tras darle un par de vueltas encuentras el cierre del medallon y lo abres");
	actionswhenUse->Addconsecuence(action);
	actionswhenUse->positionofusedOn = (Entity*)exits;

	Action* actionswhenUseOnDoor = new Action(exits, "Colocaste el medallón en la puerta, y esta hizo un click");
	ItemConsecuences* action2 = new ItemConsecuences(exits, true);
	ItemConsecuences* action2_1 = new ItemConsecuences((Entity*)item3,exits,true);
	actionswhenUseOnDoor->Addconsecuence(action2);
	actionswhenUseOnDoor->Addconsecuence(action2_1);

	item3->AddAction(actionswhenUse);
	item3->AddAction(actionswhenUseOnDoor);
	
	Item* item4 = new Item("Foto", item3, "Es una foto algo gastada que estaba dentro del medallón.");
	item4->SetPickupActionDescription("Sacas la foto del medallón y te la guardas en el bolsillo");
	
	wholeExistance.push_back(item);
	wholeExistance.push_back(item2);
	wholeExistance.push_back(item3);
	wholeExistance.push_back(item4);

	Npc* npc1 = new Npc("Bird", "A gray owl, it seems quite calm and is not bothered by your presence. She ignores you meanwhile preens her feathers and if you stare at her  enough time you see her turning her head in a funny way. Owl's things.", initialroom);
	
	Interaction* interaction = new Interaction(NULL);
	interaction->AddDialogue("El ave te mira cuando le dices hola, no está muy seguro de lo que pasa pero hace un pequeño ruido gutural hinchando el pecho. Parece querer decir que es mejor que tú");
	interaction->AddDialogue("Aunque luego de unos segundos se cansa y te mira como si ni mereciese la pena esforzarse por parecer mas poderoso que tu. Creo que he visto rintintin en su mirada");
	interaction->repetible = false;

	Interaction* interaction2 = new Interaction(NULL);
	interaction2->AddDialogue("Tras esa competición tan corta el ave ya ni se molesta en mirarte");

	Interaction* interaction3 = new Interaction(item2);
	interaction3->AddDialogue("Le acercas el trozo de carne al ave y está parece desconfiar al principio, aunque no tarda casi nada en intentar devorarlo, aunque apartas el trozo de carne a tiempo.");
	interaction3->AddDialogue("El ave te vuelve a mirar entrecerrando los ojos. Claramente eso no le ha gustado, sin embargo emprende el vuelo y se mete en el agujero de la pared. Tras unos segundos vuelve con el medallon tirandolo a tu lado.");
	interaction3->AddDialogue("Le das la carne y recoges el medallon del suelo. Se lo come antes de que puedas volver a levantar la cabeza");

	ItemConsecuences* action3 = new ItemConsecuences((Entity*)item3,player,false);
	ItemConsecuences* action3_1 = new ItemConsecuences((Item*)item3, false, "Coges el medallon");
	ItemConsecuences* action3_2 = new ItemConsecuences((Entity*)item, false, "", "Es un agujero, parece que puedes meter la mano por él pero no se si quieras... Aunque no parece haber nada dentro");
	interaction3->Addconsecuence(action3);
	interaction3->Addconsecuence(action3_1);
	interaction3->Addconsecuence(action3_2);
	interaction3->repetible = false;


	npc1->AddInteraction(interaction);
	npc1->AddInteraction(interaction3);
	npc1->AddInteraction(interaction2);

	wholeExistance.push_back(npc1);

	actualRoom = initialroom;
}

void World::ParseAction(vector<string> args) {

	if (args[0] == "Go") {
		if (args.size() > 2) cout << ">> Ok, that was confusing. Decide, Go where?" << endl;
		else if (args.size() == 2) Go(args[1]);
		else cout << ">> Go? Where? Dumb dumb" << endl;
	}
	else if (args[0] == "Examine" || args[0] == "Look") {
		if (args.size() == 1) Examine("Room");
		else if (args.size() > 2) cout << ">> You have two eyes but I don't think you can examine two things at the same time." << endl;
		else Examine(args[1]);
	}
	else if (args[0] == "Pick" || args[0] == "Take") {
		if (args.size() > 2) cout << ">> Ok, that was confusing. Decide, Pick what?" << endl;
		else if (args.size() == 2) Pick(args[1]);
		else cout << ">> Pick? What? Me?" << endl;
	}
	else if (args[0] == "Drop") {
		if (args.size() > 3) cout << ">> Ok, that was confusing. Decide, Drop what?" << endl;
		else if (args.size() == 3) Drop(args[1], args[2]);
		else if (args.size() == 2) Drop(args[1], "");
		else cout << ">> Drop? What? You?" << endl;
	}
	else if (args[0] == "Put") {
		if (args.size() > 3) cout << ">> Ok, that was confusing. Decide, Put what on where?" << endl;
		else if (args.size() == 3) Drop(args[1], args[2]);
		else cout << ">> Put? What? on Where?" << endl;
	}
	else if (args[0] == "Use") {
		if (args.size() > 2) Use(args[1], args[2]);
		else if (args.size() == 2) Use(args[1], "");
		else cout << ">> Use what? that? or that? Or that other thing? Which?!" << endl;
	}
	else if (args[0] == "Give") {
		if (args.size() > 2) Give(args[1], args[2]);
		else cout << ">> Give what? to who?" << endl;
	}
	else if (args[0] == "Talk") {
		if (args.size() > 2) cout << ">> Ok, that was confusing. Decide, Talk with who?" << endl;
		else if (args.size() == 2) Talk(args[1]);
		else cout << ">> Me? Well, I don't like to talk about me, but I consider myself a great storyteller and an adventurous voice." <<
			"I can tell you a couple of things about it. When I was young... *3 hours later*" << endl;
	}
	else if (args[0] == "Inventory") {
		if (player->Getcontent().size() > 0) Inventory(player,0);
		else cout << ">> You have fewer things than me, which is already saying a lot considering that I am just a text without a body" << endl;
	}
}

void World::Use(string nameObjectUsed, string nameObjectUsedOn) {

	Item* itemUsed = (Item*)actualRoom->CheckifContains(nameObjectUsed);
	if(itemUsed == NULL) itemUsed = (Item*)player->CheckifContains(nameObjectUsed);
	
	if (itemUsed != NULL) {
		if (nameObjectUsed == nameObjectUsedOn) cout << ">> No. Just...No. You can't do that" << endl;
		else {
			if (itemUsed->type == Type::EXITS && itemUsed->reachable && nameObjectUsedOn == "") Go(nameObjectUsed);
			else if (itemUsed->type == Type::ITEM && itemUsed->reachable) {

				if (nameObjectUsedOn == "") itemUsed->UseItem(itemUsed);
				else {
					Item* itemUsedOn = (Item*)actualRoom->CheckifContains(nameObjectUsedOn);
					if (itemUsedOn == NULL) itemUsedOn = (Item*)player->CheckifContains(nameObjectUsedOn);

					if (itemUsedOn != NULL) {
						if (itemUsedOn->reachable) {
							if (itemUsedOn->type == Type::NPC) Give(nameObjectUsed, nameObjectUsedOn);
							else itemUsed->UseItem(itemUsedOn);
						}
						else cout << ">> Can you explain to me how you will use that, exactly?" << endl;
					}
					else
					{
						cout << ">> You want to use that on what?" << endl;
					}

				}

			}
			else {
				cout << ">> Can you explain to me how you will use that, exactly?" << endl;
			}
		}
	}
	else {
		cout << ">> Use what?" << endl;
	}
}

void World::Give(string nameObjectgiven, string nameNpc) {

	Item* itemUsed = (Item*)player->CheckifContains(nameObjectgiven);

	if (itemUsed != NULL) {
			if (itemUsed->type == Type::ITEM && itemUsed->reachable) {
				
				Npc* npcUsedOn = (Npc*)actualRoom->CheckifContains(nameNpc);

				if (npcUsedOn != NULL) {
					if(npcUsedOn->reachable)npcUsedOn->ActiveInteraction(itemUsed);
					else cout << ">> Can you explain to me how you will give that, exactly?" << endl;
				}
				else
				{
					cout << ">> You want to give that to who?" << endl;
				}
			}
			else {
				cout << ">> Can you explain to me how you will give that, exactly?" << endl;
			}
	}
	else {
		cout << ">> Give what?" << endl;
	}



}

void World::Talk(string nameNpc) {
	Npc* npc = (Npc*)actualRoom->CheckifContains(nameNpc);

	if (npc != NULL) {
		if (npc->type == Type::NPC) {
			npc->ActiveInteraction(NULL);
		}
		else
		{
			cout << ">> You can talk to... that" << endl;
		}
	}
	else {
		cout << ">> Talk to who?" << endl;
	}
}

void World::Examine(string name) {

	if (name == "Room") {
		cout << ">> Look around you, you're in:" << endl;
		PrintRoom(actualRoom);
	}
	else if (name == "Me") {
		cout << ">> Look at yourself: " << endl;
		cout << "<< " << player->GetName() << " >>" << endl;
		cout << ">> " << player->GetDescription() << endl;
		PrintStats(player);
	}
	else {

		Entity* target = actualRoom->CheckifContains(name);

		if (target != NULL) {
			cout << ">> " << target->GetDescription() << endl;
		}
		else
		{
			Entity* target = player->CheckifContains(name);

			if (target != NULL) {
				cout << ">> " << target->GetDescription() << endl;
			}
			else
			{
				cout << ">> The what? You don't have that. Look again your Inventory." << endl;
			}
		}
	}
}

void World::Go(string name) {

	Exits* exit = (Exits*)actualRoom->CheckifContains(name);

	if (exit != NULL) {

		if (exit->type == Type::EXITS) {
			if (exit->reachable) {
				if (!exit->lock) {
					actualRoom = exit->GetDestination(actualRoom);

					cout << ">> " << exit->GetGoActionDescription() << " You ended up at:" << endl;
					PrintRoom(actualRoom);
				}
				else
				{
					cout << ">> It's closed" << endl;
				}
			}
			else cout << ">> And how exactly you want to do that?" << endl;
			
			
		}
		else
		{
			cout << ">> I don't think it's used like that..." << endl;
		}

	}
	else
	{
		cout << ">> Go where? I don't see that here" << endl;
	}
}

void World::Pick(string name) {

	Item* item = (Item*)actualRoom->CheckifContains(name);

	if (item != NULL) {

		if (item->type == Type::ITEM && item->pickable) {
			cout << ">> " <<  item->GetPickupActionDescription() << endl;
			if (item->reachable) {
				item->GetParent()->RemoveChild(item);
				player->AddChild(item);
			}
		}
		else
		{
			cout << ">> Why you want to grab that? Obviously you can't" << endl;
		}
	}
	else
	{
		cout << ">> Take what? I don't see that here" << endl;
	}
}

void World::Drop(string dropped, string container ) {

	if (dropped == container) cout << ">> No. Just...No. You can't do that" << endl;
	else {
		Item* itemDropped = (Item*)player->CheckifContains(dropped);
		if (itemDropped != NULL) {

			if (itemDropped->dropable) {
				if (container == "") {
					cout << ">> Drop " << itemDropped->name << endl;
					string pickdescription = "Cogiste " + itemDropped->name;
					itemDropped->SetPickupActionDescription(pickdescription);
					itemDropped->GetParent()->RemoveChild(itemDropped);
					actualRoom->AddChild(itemDropped);
				}
				else {
					Item* itemContainer = (Item*)actualRoom->CheckifContains(container);
					if (itemContainer == NULL) Item* itemContainer = (Item*)player->CheckifContains(container);
					if (itemContainer != NULL) {
						if (itemContainer->accesibleContent) {
							cout << ">> Drop " << itemDropped->name << "on" << itemContainer->name << endl;
							string pickdescription = "Cogiste " + itemDropped->name;
							if(itemContainer->type != Type::ROOM)string pickdescription = "Cogiste " + itemDropped->name + " de " + itemContainer->name;
							itemDropped->SetPickupActionDescription(pickdescription);
							itemDropped->GetParent()->RemoveChild(itemDropped);
							itemContainer->AddChild(itemDropped);
						}
						else
						{
							cout << ">> You can put things there" << endl;
						}
					}
					else
					{
						cout << ">> Where you want to drop that? Excuse me?" << endl;
					}
				}
			}
			else
			{
				cout << ">> Nah, you won't throw that away. You will 100% lost it" << endl;
			}
		}
		else
		{
			cout << ">> How are you going to throw away something you don't have? Are you ok?" << endl;
		}
	}

}


void World::Inventory(Entity* inventory,int layer) {
	list<Entity*> content = inventory->Getcontent();
	if (content.size() > 0) {
		for (Entity* child : content) {
			if (layer > 0) {
				cout << " " << setw(layer) << "|-> " << child->name << endl;
			}
			else cout << "- " << child->name << endl;
			if (child->accesibleContent)Inventory(child,layer+5);
		}
	}
}

void World::PrintRoom(Room* room) {
	cout << "<< " << room->GetName() << " >>" << endl;
	cout << ">> " << room->GetDescription() << endl;
}

void World::PrintStats(Creature* creature) {
	cout << "HP: " << creature->GetStat(Stats::HP) << endl;
	cout << "STRENGHT: " << creature->GetStat(Stats::STRENGHT) << endl;
	cout << "PERCEPTION: " << creature->GetStat(Stats::PERCEPTION) << endl;
	cout << "DEFENSE: " << creature->GetStat(Stats::DEFENSE) << endl;
}
