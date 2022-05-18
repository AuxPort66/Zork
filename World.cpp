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

	Room* lounge = new Room("Lounge", NULL, "A ordinary but messy living room, the light enters through a single window and the wooden floor creaks with each step. In the center of the room is a sturdy wooden \033[1;33mtable\033[0m accompanied by an old green \033[1;33msofa\033[0m. Next to it is an almost empty \033[1;33m bookcase\033[0m and a small bedside table with something hidden under a \033[1;33msheet\033[0m. There are two doors, a \033[1;33mbig\033[0m door at the east of the room and a \033[1;33msmall\033[0m one white door next to the bookcase. Smells of tobacco.");
	Room* bathroom = new Room("Bathroom", NULL, "A shabby bathroom, the tiles are a bit dirty and it smells musty, but somehow it's not the worst area of the house. There is a \033[1;33m sink \033[0m with some used \033[1;33mcandles\033[0m], a \033[1;33m mirror \033[0m covered with a garbage bag and gray \033[1;33m closet \033[0m. And a \033[1;33m small \033[0m door to the Lounge ");
	Room* kitchen = new Room("Kitchen", NULL, "A spacious, bright kitchen with a large white \033[1;33mfridge\033[0m in one corner and a much cleaner countertop than the rest of the house. A\033[1;33m big \033[0m door to the Lounge. And even the \033[1;33m trash \033[0m bin appears to be tidy and empty. It would be fantastic if it weren't for the fact that in the middle of the room there is the \033[1;33mcorpse\033[0m of what looks like a middle-aged man.");
	Room* basement = new Room("Basement", NULL, "it's really dark. You Only see the \033[1;33m hatch\033[0m");
	Room* dark = new Room("DARK", NULL, "You end up lying on the ground, you don't know where you are, it's so dark that you hardly recognize if there is a ground or not. You try to get up but before you can hear a scream and see a bluish flash cut through the darkness.");
	basement->accesibleContent = false;

	player = new Player("Blake", lounge, "A person, I guess");
	player->ChangeStat(Stats::PERCEPTION, 1);
	player->ChangeStat(Stats::STRENGHT, 2);
	player->ChangeStat(Stats::DEFENSE, 3);

	wholeExistance.push_back(player);

	wholeExistance.push_back(lounge);
	wholeExistance.push_back(bathroom);
	wholeExistance.push_back(kitchen);
	wholeExistance.push_back(basement);

	Exits* kitchenDoor = new Exits("Big",lounge,kitchen,"There is a \033[1;33m big\033[0m door in the middle of the wall, it has a knob but no lock and it seems to lead into the kitchen.");
	kitchenDoor->SetGoActionDescription("You went through the big door");
	Exits* bathroomDoor = new Exits("Small",lounge,bathroom,"There is a \033[1;33m small\033[0m door on the side of the wall, next to the \033[1;33m bookcase\033[0m. It is painted white and it's mid open, it seems to lead to the bathroom");
	bathroomDoor->SetGoActionDescription("You went through the small door");

	wholeExistance.push_back(kitchenDoor);
	wholeExistance.push_back(bathroomDoor);

	Item* tableLounge = new Item("Table",lounge,"A large wooden table with some dust, it has only a red \033[1;33m book\033[0m on it. It seems that it has some papers inside and it is the cleanest thing in the place");
	tableLounge->pickable = false;
	tableLounge->noCapacity = false;

	Item* book = new Item("Book", tableLounge, "A red \033[1;33m book\033[0m with a couple of papers inside, in one of them you can see a draw, two triangles forming an hourglass.");
	book->usedWhenPick = true;

	Action* pickBook = new Action(book, "You pick up the book");
	ItemConsecuences* clearTable = new ItemConsecuences((Entity*)tableLounge, false, "", "A large wooden table with some dust");
	pickBook->Addconsecuence(clearTable);

	book->AddAction(pickBook);

	Item* bookcase = new Item("Bookshelf",lounge, "An almost empty shelf, has a couple of misplaced books and anything else");
	bookcase->pickable = false;
	bookcase->noCapacity = false;

	wholeExistance.push_back(tableLounge);
	wholeExistance.push_back(bookcase);


	Item* sheet = new Item("Sheet", lounge, "A \033[1;33m sheet\033[0m thrown over what looks like an open cage. You can hear some very slight noises inside.");
	sheet->SetPickupActionDescription("You fold the sheet and pick it up, although you don't think it will do much.");
	sheet->usedWhenPick = true;
	sheet->accesibleContent = false;

	wholeExistance.push_back(sheet);

	Item* fridge = new Item("Fridge", kitchen, "A fridge");
	fridge->pickable = false;
	fridge->noCapacity = false;
	fridge->havedropped = 3;


	Item* meat = new Item("Meat", fridge, "It's a piece of \033[1;33m meat\033[0m that you took out of the fridge, the only thing that was left inside");
	meat->SetPickupActionDescription("You take the piece of meat, it's half day from not being edible anymore, but maybe it's useful for something");
	meat->dropable = false;
	meat->lostOnUse = true;

	Item* pizza = new Item("Pizza", fridge, "It's a piece of pineapple \033[1;33m pizza\033[0m...uhg");
	pizza->SetPickupActionDescription("You take the pinapple pizza, because it doesn't even deserve to be in the fridge");
	pizza->dropable = true;

	/*Item* bottle = new Item("Bottle", fridge, "It's a \033[1;33m bottle\033[0m with some water");
	bottle->SetPickupActionDescription("You take the water, maybe it's usefull");
	bottle->dropable = false;
	*/

	Item* trash = new Item("Trash", kitchen, "A trash bin");
	trash->pickable = false;
	trash->noCapacity = false;


	Item* corpse = new Item("Corpse", kitchen, "The body of a middle-aged man. He appears to have a lighter in his pocket. He has a claw-shaped wound on his neck, the outline is bluish. His hands are stained with something gray, like ash or dust.");
	corpse->pickable = false;

	Item* lighter = new Item("Lighter", corpse, "A red lighter, a cheap one");
	lighter->usedWhenPick = true;
	lighter->dropable = false;
	lighter->SetPickupActionDescription("You take the lighter of the corpse");
	
	Action* pickLighter = new Action(lighter, "You move the body a little bit to reach the lighter");
	ItemConsecuences* clearBody = new ItemConsecuences((Entity*)corpse, false, "", "The body of a middle - aged man.He has a claw - shaped wound on his neck, the outline is bluish.His hands are stained with something gray, like ash or dust.");
	clearBody->reversible = false;
	pickLighter->Addconsecuence(clearBody);
	lighter->AddAction(pickLighter);


	Item* sink = new Item("Sink", bathroom, "A sink it have a couple of used \033[1;33m candles\033[0m");
	sink->pickable = false;

	Item* candle = new Item("Candle", sink, "The only candle that can still be lit");
	candle->usedWhenPick = true;
	candle->dropable = false;

	Action* pickCandle = new Action(candle, "You pick up the unique candle that can still be lit");
	ItemConsecuences* clearSink = new ItemConsecuences((Entity*)sink, false);
	pickCandle->Addconsecuence(clearSink);
	candle->AddAction(pickCandle);

	Action* litCandle = new Action(candle, "You lit the unique candle that can still be lit");
	ItemConsecuences* candletoInventory = new ItemConsecuences((Entity*)candle, player, false);
	ItemConsecuences* candleDescription = new ItemConsecuences((Entity*)candle, false, "", "A lit candle, now you can see everything! Which is not good considering the state of this house");
	ItemConsecuences* basementLight = new ItemConsecuences((Entity*)basement, false);
	ItemConsecuences* basementDescription = new ItemConsecuences((Entity*)basement, false, "", "A stone basement. There's a \033[1;33m bookcase\033[0m and a wood \033[1;33m stove \033[0m, as well as the \033[1;33m hatch \033[0myou went down through. But the most surprising of all is the center of the room. On the floor there are large gray \033[1;33m marks\033[0m, and in the center of these a full-length \033[1;33m mirror\033[0m.");
	litCandle->Addconsecuence(clearSink);
	litCandle->Addconsecuence(candletoInventory);
	litCandle->Addconsecuence(candleDescription);
	litCandle->Addconsecuence(basementLight);
	litCandle->Addconsecuence(basementDescription);

	lighter->AddAction(litCandle);

	Item* mirror = new Item("Mirror", bathroom, "A mirror covered with a garbage bag");
	mirror->pickable = false;

	Action* useMirror = new Action(mirror, "You remove the garbage bag");
	ItemConsecuences* clearMirror = new ItemConsecuences((Entity*)mirror, false,"", "A normal mirror");
	useMirror->Addconsecuence(clearMirror);
	mirror->AddAction(useMirror);

	Item* closet = new Item("Closet", bathroom, "A closet, the top looks scratched. When you look out you see a \033[1;33m hole\033[0m in the wall.");
	closet->pickable = false;
	closet->noCapacity = false;


	Item* hole = new Item("Hole", closet, "It's a hole, it looks like you can put your hand through it but I don't know if you want to... It also seems pretty deep. Although in the background I think there is a kind of \033[1;33m medallion\033[0m but you don't reach");
	hole->pickable = false;
	hole->SetPickupActionDescription("How can you pick up a hole?");

	Item* sofa = new Item("Sofa", lounge, "An old green \033[1;33m sofa\033[0m, next to it there are marks on the floor, as if it had been dragged.");
	sofa->accesibleContent = false;
	wholeExistance.push_back(sofa);

	Exits* hatch = new Exits("Hatch", lounge, basement, "A hatch under the \033[1;33m sofa\033[0m, it has a lock but it has a very strange triangular shape.It has like ash traces on the edges");
	hatch->SetGoActionDescription("You opened the hatch letting some light into the basement, but not enough to see anything beyond the stairs down");
	hatch->lock = true;
	hatch->alwaysReachable = true;

	wholeExistance.push_back(hatch);

	ItemConsecuences* freeHatch = new ItemConsecuences((Entity*)hatch, lounge, false);
	Action* useSofa = new Action(sofa, "You move the sofa and discover a \033[1;33m hatch\033[0m on the floor.");
	useSofa->Addconsecuence(freeHatch);

	sofa->AddAction(useSofa);


	Item* medallion = new Item("Medallion", player, "Triangular medallion, seems to contain something inside");
	medallion->SetPickupActionDescription("You don't get to the medallion, it's too far into the hole");
	medallion->accesibleContent = false;
	medallion->reachable = false;

	ItemConsecuences* useMedallion = new ItemConsecuences((Entity*)medallion, true);
	useMedallion->reversible = false;
	Action* openMedallion = new Action(medallion, "After giving it a couple of turns you find the closure of the medallion and open it. It has a \033[1;33m photo\033[0m");
	openMedallion->Addconsecuence(useMedallion);

	Action* putMedalliononHatch = new Action(hatch, "You placed the medallion on the hatch, and it clicked.");
	ItemConsecuences* action2 = new ItemConsecuences(hatch, true);
	ItemConsecuences* action2_1 = new ItemConsecuences((Entity*)medallion, hatch, true);
	putMedalliononHatch->Addconsecuence(action2);
	putMedalliononHatch->Addconsecuence(action2_1);

	medallion->AddAction(openMedallion);
	medallion->AddAction(putMedalliononHatch);

	Item* photo = new Item("Photo", medallion, "It's a slightly worn photo that was inside the locket. A small kid, similar to the man in the kitchen, same nose and eyes. Although the photo looks too old and you saw nothing that proves that a child lived in this house.");
	photo->pickable = false;

	Npc* owl = new Npc("Owl", "A gray owl, it seems quite calm and is not bothered by your presence. She ignores you meanwhile preens her feathers and if you stare at her  enough time you see her turning her head in a funny way. Owl's things.", sheet);

	Interaction* interaction = new Interaction(NULL);
	interaction->AddDialogue("The bird looks at you when you say hello, it's not sure what's going on but it makes a small guttural noise puffing out its chest. He seems to want to say that he is better than you");
	interaction->AddDialogue("Although after a few seconds he gets tired and looks at you as if it's not even worth trying to seem more powerful than you. I think he has put on a mocking look.");
	interaction->repetible = false;

	Interaction* interaction2 = new Interaction(NULL);
	interaction2->AddDialogue("After that short competition, the bird doesn't even bother to look at you anymore.");

	Interaction* interaction3 = new Interaction(meat);
	interaction3->AddDialogue("You approach the piece of meat to the bird and it seems suspicious at first, although it takes almost no time to try to devour it, although you move the piece of meat away in time.");
	interaction3->AddDialogue("The bird looks at you again, narrowing its eyes. Clearly it didn't like that, however it takes flight and goes into the bathroom. After a few seconds it returns with a medallion, throwing it next to you.");
	interaction3->AddDialogue("You give him the meat and pick up the \033[1;33m medallion\033[0m from the ground. He eats it before you can raise your head again");

	ItemConsecuences* action3 = new ItemConsecuences((Entity*)medallion, player, false);
	ItemConsecuences* action3_1 = new ItemConsecuences((Item*)medallion, false, "Pick up the medallion");
	ItemConsecuences* action3_2 = new ItemConsecuences((Entity*)hole, false, "", "It's a hole, it looks like you can put your hand through it but I don't know if you want to... Although doesn't seem to be anything inside");
	interaction3->Addconsecuence(action3);
	interaction3->Addconsecuence(action3_1);
	interaction3->Addconsecuence(action3_2);
	interaction3->repetible = false;

	owl->AddInteraction(interaction);
	owl->AddInteraction(interaction3);
	owl->AddInteraction(interaction2);

	wholeExistance.push_back(owl);
	
	Action* useSheet = new Action(sheet, "You pull the sheet and discover a cage with an \033[1;33m owl\033[0m");
	ItemConsecuences* freeOwl = new ItemConsecuences((Entity*)owl, lounge, false);
	ItemConsecuences* changeLounge = new ItemConsecuences((Entity*)lounge,false, "", "A ordinary but messy living room, the light enters through a single window and the wooden floor creaks with each step. In the center of the room is a sturdy wooden \033[1;33mtable\033[0m accompanied by an old green \033[1;33msofa\033[0m. Next to it is an almost empty \033[1;33bookcase\033[0m and a small bedside table with a cage and a \033[1;33mowl\033[0m, it's looking you. There are two doors, a \033[1;33mbig\033[0m door at the east of the room and a \033[1;33msmall\033[0m one white door next to the bookcase. Smells of tobacco.");
	useSheet->Addconsecuence(freeOwl);
	useSheet->Addconsecuence(changeLounge);

	sheet->AddAction(useSheet);

	Item* bookshelf = new Item("Bookshelf", basement, "An almost empty shelf, has a couple of misplaced books and a \033[1;33m archive\033[0m");
	bookshelf->pickable = false;
	bookshelf->noCapacity = false;

	wholeExistance.push_back(bookshelf);

	Item* archive = new Item("Archive", bookshelf, "A archive full of documents. You see a bunch of research about mysterious attacks, news gatherings, studies on ancient artifacts of Celtic cultures, and a \033[1;33m receipt\033[0m.");
	archive->usedWhenPick = true;

	Action* pickArchive = new Action(archive, "You pick up the Archive");
	ItemConsecuences* clearbookshelf = new ItemConsecuences((Entity*)bookshelf, false, "", "An almost empty shelf, has a couple of misplaced books");
	pickArchive->Addconsecuence(clearbookshelf);

	archive->AddAction(pickArchive);

	Item* receipt = new Item("Receipt", archive, "A receipt for a purchase for a large sum, too much, attached to a letter mentioning a mirror");
	receipt->pickable = false;

	Item* stove = new Item("Stove", basement, "A wood stove turned off, still have some wood but it looks like someone has removed the ashes");
	stove->pickable = false;
	stove->accesibleContent = false;

	Item* ashes = new Item("Ashes", stove, "Freshly made ashes, be careful, they burn a little.");
	ashes->dropable = false;
	ashes->SetPickupActionDescription("With care you take the most coldest ashes");

	Item* marks = new Item("Marks", basement, "Gray marks on the ground. It is as if it were ash but it has remained attached to the wood. The drawing looks incomplete");
	marks->pickable = false;

	ItemConsecuences* tpPlayer = new ItemConsecuences((Entity*)player,dark, false);
	tpPlayer->reversible = false;
	Action* useAshes = new Action(marks, "You take the ashes and finish the drawing on the ground, an hourglass. As soon as you put the last stroke, the ashes heat up even more and stay attached to the wood. You hear a tinkling, louder this time. You raise your head but everything goes black.");
	useAshes->Addconsecuence(tpPlayer);
	ashes->AddAction(useAshes);
	

	ItemConsecuences* changeStove = new ItemConsecuences((Entity*)stove, false, "","A wood stove turned on, the wood is burning inside making new ashes");
	changeStove->reversible = false;
	ItemConsecuences* putAshes = new ItemConsecuences((Entity*)stove, false);
	putAshes->reversible = false;
	Action* litPaper = new Action(stove, "You use the lighter on the remains of wood, a little fire starts");
	litPaper->Addconsecuence(changeStove);
	litPaper->Addconsecuence(putAshes);
	lighter->AddAction(litPaper);

	Item* mirrorBasement = new Item("Mirror", basement, "A full-length mirror has engravings that seem to be some language you don't understand. It has an imposing aura and when you stare at it you think you can hear a kind of tinkling.");
	mirrorBasement->pickable = false;

	actualRoom = lounge;
}

bool World::isFinish() {
	if (actualRoom->name == "DARK") {
		cout << _RESTART "With the little that was left of you you run away, seeing the basement again as soon as you take the first step. You turn confused. The mirror is gone.\n" << endl;
	    cout << "You decide to leave, it has been a horrible experience.You told the rest of the police what happened.But no one believed you.Your career as an inspector pretty much stalled after that.But the worst thing is that now, the mirrors that are covered are the ones in your house.\n" << endl;
		cout << "Just in case..." << endl;
			
		return true;
	}
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
	else {
		cout << ">> I don't understand you" << endl;
	}

	if (player->tp) {
		actualRoom = (Room*)player->GetParent();
		Examine("Room");
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

				if (nameObjectUsedOn == "") {
					itemUsed->UseItem(itemUsed);
					itemUsed->usedWhenPick = false;
				}
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
			if (target->havedropped > 0) {
				if (target->Getcontent().size() == 0) {
					target->havedropped = 0;
				}
				else
				{
					if (target->Getcontent().front()->dropped)cout << ">> And you drop all of this here:" << endl;
					else cout << ">> And it has all of this:" << endl;
					for (Entity* child : target->Getcontent()) {
						if (child->dropped || !target->Getcontent().front()->dropped) cout << "  |-> " << child->name << endl;
					}
					if (target->havedropped > 5) cout << ">> Do you have diogenes?" << endl;
				}
			}
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
					actualRoom->RemoveChild(player);

					actualRoom = exit->GetDestination(actualRoom);
					cout << ">> " << exit->GetGoActionDescription() << " You ended up at:" << endl;
					PrintRoom(actualRoom);
					player->SetParent(actualRoom);
					actualRoom->AddChild(player);
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
			if (item->reachable) {

				if (item->dropped) {
					item->GetParent()->havedropped--;
					item->dropped = false;
				}
				if (item->usedWhenPick) {
					item->UseItem(item);
					item->usedWhenPick = false;
				}
				item->GetParent()->RemoveChild(item);
				player->AddChild(item);
			}
			cout << ">> " << item->GetPickupActionDescription() << endl;
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
					string pickdescription = "You pick up " + itemDropped->name;
					itemDropped->SetPickupActionDescription(pickdescription);
					itemDropped->GetParent()->RemoveChild(itemDropped);
					actualRoom->AddChild(itemDropped);
					itemDropped->dropped = true;
					actualRoom->havedropped++;
				}
				else {
					Item* itemContainer = (Item*)actualRoom->CheckifContains(container);
					if (itemContainer == NULL) Item* itemContainer = (Item*)player->CheckifContains(container);
					if (itemContainer != NULL) {
						if (itemContainer->accesibleContent && !itemContainer->noCapacity) {
							cout << ">> Drop " << itemDropped->name << " on " << itemContainer->name << endl;
							string pickdescription = "You pick up " + itemDropped->name;
							if(itemContainer->type != Type::ROOM)string pickdescription = "Pick up " + itemDropped->name + " of " + itemContainer->name;
							itemDropped->SetPickupActionDescription(pickdescription);
							itemDropped->GetParent()->RemoveChild(itemDropped);
							itemContainer->AddChild(itemDropped);
							itemDropped->dropped = true;
							itemContainer->havedropped++;
						}
						else
						{
							cout << ">> No?" << endl;
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
	cout << "\033[1;4;33m<< " << room->GetName() << " >>" << endl;
	cout << "\033[0m>> " << room->GetDescription() << endl;

	if (room->havedropped > 0) {
		if (room->Getcontent().front()->dropped)cout << ">> And you drop all of this here:" << endl;
		else cout << ">> And it has all of this:" << endl;
		for (Entity* child : room->Getcontent()) {
			if (child->dropped) cout << "  |-> " << child->name << endl;
		}
		if (room->havedropped > 5) cout << ">> Do you have diogenes?" << endl;
	}

}

void World::PrintStats(Creature* creature) {
	cout << "HP: " << creature->GetStat(Stats::HP) << endl;
	cout << "STRENGHT: " << creature->GetStat(Stats::STRENGHT) << endl;
	cout << "PERCEPTION: " << creature->GetStat(Stats::PERCEPTION) << endl;
	cout << "DEFENSE: " << creature->GetStat(Stats::DEFENSE) << endl;
}
