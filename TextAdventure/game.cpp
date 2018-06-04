// game.cpp
#include "stdafx.h"
#include <iostream>
#include <string>
#include "healthpotion.h"
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

	// initialise room exits
	destroyedBase->setExit("down",destroyedBaseBasement);

	destroyedBaseBasement->setExit("up",destroyedBase);

	//Set room Inventory
	destroyedBaseBasement->getInventory()->addItem(new Item());
	destroyedBaseBasement->getInventory()->addItem(new Item());
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
	std::cout << "Thank you for playing. Goodbye!" << std::endl;
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
		std::cout << "There is no door!" << std::endl;
	} else {

		//See if player has enough health left
		if (player.isAlive()) {
			player.setCurrentRoom(nextRoom);
			std::cout << player.getCurrentRoom()->getLongDescription() << std::endl;
			return;
		}
		else if(!player.isAlive()){
			std::cout << "Player has died!" << std::endl;
			return;
		}
	}
}

void Game::grab(Command cmd) {
	if (!cmd.hasSecondWord()) {
		// if there is no second word, we don't know what to grab...
		std::cout << "Grab what?" << std::endl;
		return;
	}

	for (int i = 0; i < player.getCurrentRoom()->getInventory()->getSize(); i++) {
		if (cmd.getSecondWord() == player.getCurrentRoom()->getInventory()->getItem(i)->getItemName()) {
			//Grab the item
			if (player.getInventory()->addItem(player.getCurrentRoom()->getInventory()->getItem(i))) {
				player.getCurrentRoom()->getInventory()->removeItem(i);
				std::cout << "Grabbed a " << cmd.getSecondWord() << std::endl;
			}
			return;
		}
	}

	std::cout << "That item is not in the room!" << std::endl;
	return;
}

void Game::consume(Command cmd) {
	if (!cmd.hasSecondWord()) {
		// if there is no second word, we don't know what to consume...
		std::cout << "Consume what?" << std::endl;
		return;
	}

	for (int i = 0; i < player.getInventory()->getSize(); i++) {
		if (cmd.getSecondWord() == player.getInventory()->getItem(i)->getItemName()) {
			if (player.getInventory()->getItem(i)->getItemName() == "HealthPotion") {
				int oldHealth = player.getHealth();
				player.heal(20);
				std::cout << "You drank a Health Potion" << std::endl;
				std::cout << "Health: " << oldHealth << " >> " << player.getHealth() << std::endl;
				player.getInventory()->removeItem(i);
			}
			else {
				std::cout << "You cant consume that Item" << std::endl;
			}
			return;
		}
	}

	std::cout << "You dont have that consumable" << std::endl;
}

void Game::drop(Command cmd) {
	if (!cmd.hasSecondWord()) {
		// if there is no second word, we don't know what to drop...
		std::cout << "drop what?" << std::endl;
		return;
	}

	for (int i = 0; i < player.getInventory()->getSize(); i++) {
		if (cmd.getSecondWord() == player.getInventory()->getItem(i)->getItemName()) {
			player.getCurrentRoom()->getInventory()->addItem(player.getInventory()->getItem(i));
			player.getInventory()->removeItem(i);
			std::cout << "Dropped: " << cmd.getSecondWord() << std::endl;
			return;
		}
	}
	std::cout << "You dont have that Item" << std::endl;
	return;
}

bool Game::processCommand(Command cmd)
{
	bool wantToQuit = false;

	if(cmd.isUnknown()) {
		std::cout << "I don't know what you mean..." << std::endl;
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
		std::cout << player.getCurrentRoom()->getLongDescription() << std::endl;
		std::cout << player.getCurrentRoom()->getInventoryString() << std::endl;
	}
	else if (commandWord.compare("grab") == 0) {
		this->grab(cmd);
	}
	else if (commandWord.compare("inventory") == 0) {
		std::cout << "Weight: " << player.getInventory()->getWeight() << "/" << player.getInventory()->getMaxWeight() << std::endl;
		std::cout << player.getInventoryString() << std::endl;
	}
	else if (commandWord.compare("consume") == 0) {
		this->consume(cmd);
	}
	else if (commandWord.compare("drop") == 0) {
		this->drop(cmd);
	}

	return wantToQuit;
}

void Game::printWelcome()
{
	std::cout << std::endl;
	std::cout << "Welcome my dear user...." << std::endl;
	std::cout << "You have arrived in a magical world" << std::endl;
	std::cout << "Type 'help' if you need help." << std::endl;
	std::cout << std::endl;
	std::cout << player.getCurrentRoom()->getLongDescription() << std::endl;
}

void Game::printHelp()
{
	/*std::cout << "You are lost. You are alone. You wander" << std::endl;
	std::cout << "around at the university." << std::endl;
	std::cout << std::endl;*/
	std::cout << "Your command words are:" << std::endl;
	parser.showCommands();
}
