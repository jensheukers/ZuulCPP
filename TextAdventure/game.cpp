// game.cpp
#include "stdafx.h"
#include <iostream>
#include <string>
#include "game.h"

Game::Game()
{
	this->player.setCurrentRoom(NULL);
	this->createRooms();
}

Game::~Game()
{

}

void Game::createRooms()
{
	// create the rooms
	destroyedBase = new Room("in a destroyed military base in the jungle.");
	destroyedBaseBasement = new Room("in the basement of the military base.");
	destroyedOutside = new Room("outside the destroyed military base");

	// initialise room exits
	destroyedBase->setExit("down",destroyedBaseBasement);
	destroyedBase->setExit("left",destroyedOutside);

	destroyedBaseBasement->setExit("up",destroyedBase);

	destroyedOutside->setExit("right",destroyedBase);

	//Lock the rooms that need to be locked
	destroyedOutside->setRequiredKey(new Key());
	destroyedOutside->setLock(true);

	//Set room Inventory
	destroyedBaseBasement->getInventory()->addItem(new Key());
	destroyedBaseBasement->getInventory()->addItem(new HealthPotion());

	this->player.setCurrentRoom(destroyedBase);  // start game outside

	
}

void Game::play()
{
	this->printWelcome();

	bool finished = false;

	player.getInventory()->setMaxWeight(45);

	while ( !finished ) {
		Command command = parser.getCommand();
		finished = processCommand(command);
	}
}

void Game::goRoom(Command cmd)
{
	if(!cmd.hasSecondWord()) {
		// if there is no second word, we don't know where to go...
		std::cout << "Go where?" << std::endl;
		return;
	}

	std::string direction = cmd.getSecondWord();

	// Try to leave current room.
	Room* nextRoom = player.getCurrentRoom()->getExit(direction);

	if (nextRoom == NULL) {
		Writer::printLongLine();
		Writer::printSpc();
		Writer::printEmpty(5);
		Writer::printLine("There is no door!");
		Writer::printLongLine();
	}
	else {
		//See if player has enough health left
		if (player.isAlive()) {
			if (nextRoom->getLockState()) {
				if (!player.hasItem(nextRoom->getKey())) {
					Writer::printLongLine();
					Writer::printSpc();
					Writer::printEmpty(5);
					Writer::printLine("That room is locked!");
					Writer::printEmpty(5);
					Writer::printLine(Writer::append("You require a : ", nextRoom->getKeyName()));
					Writer::printLongLine();
					return;
				}
				else {
					nextRoom->setLock(false);
					Writer::printLongLine();
					Writer::printSpc();
					Writer::printLine("You have unlocked a room!");
					Writer::printLongLine();
				}
			}
		}
		else if(!player.isAlive()){
			std::cout << "Player has died!" << std::endl;
			return;
		}

		player.setCurrentRoom(nextRoom);
		Writer::printLongLine();
		Writer::printSpc();
		Writer::printLine(player.getCurrentRoom()->getLongDescription());
		Writer::printLongLine();
		return;
	}
}

void Game::grab(Command cmd) {
	if (!cmd.hasSecondWord()) {
		// if there is no second word, we don't know what to grab...
		Writer::printLongLine();
		Writer::printSpc();
		Writer::printEmpty(5);
		Writer::printLine("I dont know what to grab..");
		Writer::printLongLine();
		return;
	}


	//Determine if user typed a integer
	std::string secondTypeWord;

	secondTypeWord = cmd.getSecondWord();
	for (int i = 0; i < player.getCurrentRoom()->getInventory()->getSize(); i++) {
		if (secondTypeWord == player.getCurrentRoom()->getInventory()->getItem(i)->getItemName()) {
			//Grab the item
			if (player.getInventory()->addItem(player.getCurrentRoom()->getInventory()->getItem(i))) {
				player.getCurrentRoom()->getInventory()->removeItem(i);

				Writer::printLongLine();
				Writer::printSpc();
				Writer::printEmpty(5);
				Writer::printLine(Writer::append("You grabbed a: ", cmd.getSecondWord()));
				Writer::printLongLine();
			}
			return;
		}
	}

	std::cout << "That item is not in the room!" << std::endl;
	return;
}

void Game::consume(Command cmd) {
	Writer::printLongLine();
	Writer::printSpc();
	if (!cmd.hasSecondWord()) {
		// if there is no second word, we don't know what to consume...
		Writer::printEmpty(5);
		Writer::printLine("I dont know what to consume");
		Writer::printLongLine();
		return;
	}


	for (int i = 0; i < player.getInventory()->getSize(); i++) {
		if (cmd.getSecondWord() == player.getInventory()->getItem(i)->getItemName()) {
			if (player.getInventory()->getItem(i)->getItemName() == "HealthPotion") {
				int oldHealth = player.getHealth();
				player.heal(20);
				Writer::printLine("You drank a Health Potion");
				Writer::printSpc();
				Writer::printLine(Writer::append(Writer::append("Health: ", std::to_string(oldHealth)), Writer::append(" >> ", std::to_string(player.getHealth()))));
				player.getInventory()->removeItem(i);
			}
			else {
				Writer::printLine("You cant consume that Item");
				Writer::printLongLine();
			}
			return;
		}
	}

	Writer::printLine("You dont have that consumable");
	Writer::printLongLine();
}

void Game::drop(Command cmd) {
	if (!cmd.hasSecondWord()) {
		// if there is no second word, we don't know what to drop...
		Writer::printLongLine();
		Writer::printSpc();
		Writer::printEmpty(5);
		Writer::printLine("drop what?");
		Writer::printLongLine();
		return;
	}

	for (int i = 0; i < player.getInventory()->getSize(); i++) {
		if (cmd.getSecondWord() == player.getInventory()->getItem(i)->getItemName()) {
			player.getCurrentRoom()->getInventory()->addItem(player.getInventory()->getItem(i));
			player.getInventory()->removeItem(i);

			Writer::printLongLine();
			Writer::printSpc();
			Writer::printEmpty(5);
			Writer::printLine(Writer::append("Dropped: ", cmd.getSecondWord()));
			Writer::printLongLine();
			return;
		}
	}
	Writer::printLine("You dont have that Item");
	return;
}

bool Game::processCommand(Command cmd)
{
	bool wantToQuit = false;

	if(cmd.isUnknown()) {
		Writer::printLine("I don't know what you mean...");
		return false;
	}

	std::string commandWord = cmd.getCommandWord();

	if (commandWord.compare("help") == 0) {
		this->printHelp();
	} else if (commandWord.compare("go") == 0) {
		this->goRoom(cmd);
	} else if (commandWord.compare("quit") == 0) {
		//wantToQuit = quit(command);
		wantToQuit = true;
	} 
	else if (commandWord.compare("look") == 0) {	
		std::vector<std::string> items = player.getCurrentRoom()->getInventoryItems();

		Writer::printLongLine();
		Writer::printSpc();
		Writer::printEmpty(5);
		Writer::printLine("Room Description:");
		Writer::printEmpty(7);
		Writer::printLine(player.getCurrentRoom()->getLongDescription());
		Writer::printEmpty(7);
		Writer::printLine(player.getCurrentRoom()->getExitString());

		if (items.size() != 0) {
			Writer::printSpc();
			Writer::printEmpty(5);
			Writer::printLine("These Items are found in the room:");

			for (int i = 0; i < items.size(); i++) {
				Writer::printEmpty(7);
				Writer::printText(std::to_string(i));
				Writer::printEmpty(2);
				Writer::printLine(items[i]);
			}
			Writer::printSpc();
			Writer::printEmpty(5);
			Writer::printLine("-Type grab then the name of the Item to grab!");
			Writer::printLongLine();
		}
		else {
			Writer::printSpc();
			Writer::printEmpty(5);
			Writer::printLine("There are no Items in this room!");
			Writer::printLongLine();
		}
	}
	else if (commandWord.compare("grab") == 0) {
		this->grab(cmd);
	}
	else if (commandWord.compare("inventory") == 0) {
		std::vector<Item*> invItems = player.getInventory()->getContents();

		Writer::printLongLine();
		Writer::printSpc();
		Writer::printEmpty(5);
		std::cout << "Weight: " << player.getInventory()->getWeight() << "/" << player.getInventory()->getMaxWeight() << std::endl;
		Writer::printSpc();
		Writer::printEmpty(5);
		Writer::printLine("Inventory:");

		for (int i = 0; i < invItems.size(); i++) {
			Writer::printEmpty(7);
			Writer::printText(std::to_string(i));
			Writer::printEmpty(2);
			Writer::printLine(invItems[i]->getItemName());
		}


		Writer::printLongLine();
	
	}
	else if (commandWord.compare("consume") == 0) {
		this->consume(cmd);
	}
	else if (commandWord.compare("drop") == 0) {
		this->drop(cmd);
	}
	else if (commandWord.compare("clear") == 0) {
		this->clear();
	}

	return wantToQuit;
}

void Game::printWelcome()
{
	std::cout << std::endl;
	Writer::printLongLine();
	Writer::printSpc();
	Writer::printEmpty(5);
	Writer::printLine("Welcome to GAMENAME, type help for commands...");
	Writer::printSpc();
	Writer::printEmpty(5);
	Writer::printLine(player.getCurrentRoom()->getLongDescription());
	Writer::printLongLine();
}

void Game::printHelp()
{
	/*std::cout << "You are lost. You are alone. You wander" << std::endl;
	std::cout << "around at the university." << std::endl;
	std::cout << std::endl;*/
	Writer::printLongLine();
	Writer::printSpc();
	Writer::printEmpty(5);
	Writer::printLine("Your command words are:");
	std::vector<std::string> commands = parser.getCommands();

	for (int i = 0; i < commands.size(); i++) {
		Writer::printEmpty(7);
		Writer::printText(std::to_string(i));
		Writer::printEmpty(2);
		Writer::printLine(commands[i]);
	}

	Writer::printLongLine();
}
/*
* Clear the console.
*/
void Game::clear() {
	system("cls");
}
/*
void Game::attack(Command cmd) {
	if (player.getCurrentRoom()->hasEnemy()) {
		if (!cmd.hasSecondWord()) {
			// if there is no second word, we don't know what to use as a weapon...
			Writer::printLongLine();
			Writer::printSpc();
			Writer::printEmpty(5);
			Writer::printLine("What weapon should we use?");
			Writer::printLongLine();
			return;
		}
		std::string weaponString = cmd.getSecondWord();
		
		//Check the inventory for the weapon

		for (int i = 0; i < player.getInventory()->getSize(); i++) {
			if (player.getInventory()->getItem(i)->getItemName() == weaponString) {
				Item* weapon = player.getInventory()->getItem(i);
			}
		}
	}
	else {
		Writer::printLongLine();
		Writer::printSpc();
		Writer::printEmpty(5);
		Writer::printLine("There is nothing to attack!");
		Writer::printLongLine();
	}
}

void Game::counterAttack() {

}
*/
