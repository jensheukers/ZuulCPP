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
	prisonCell = new Room("in your prison cell.");
	prisonCellBlock = new Room("in the prison block hall");
	prisonCellUnder = new Room("in a room underneath your prison bed");

	// initialise room exits
	prisonCell->setExit("down", prisonCellUnder);
	prisonCell->setExit("left", prisonCellBlock);

	prisonCellUnder->setExit("up", prisonCell);

	prisonCellBlock->setExit("right", prisonCell);

	//Lock the rooms that need to be locked
	prisonCellBlock->setRequiredKey(new Key());
	prisonCellBlock->setLock(true);

	//Set room Inventory
	prisonCellUnder->getInventory()->addItem(new Key());
	prisonCellUnder->getInventory()->addItem(new HealthPotion());
	prisonCell->getInventory()->addItem(new Sword());

	//Set room enemy's
	prisonCellUnder->setEnemy(new Roamer());
	prisonCellBlock->setEnemy(new Guard());

	this->player.setCurrentRoom(prisonCell);  // start game outside

	
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
	if (player.getCurrentRoom()->hasEnemy()) {
		Writer::printLongLine();
		Writer::printSpc();
		Writer::printEmpty(5);
		Writer::printLine("You have to eliminate your enemy first!");
		Writer::printLongLine();
		return;
	}
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
					Writer::printEmpty(5);
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
		Writer::printEmpty(5);
		Writer::printLine(player.getCurrentRoom()->getLongDescription());

		if (player.getCurrentRoom()->hasEnemy()) {
			Writer::printEmpty(5);
			Writer::printLine(Writer::append("There is a: ", player.getCurrentRoom()->getEnemy()->getName()));
			Writer::printEmpty(5);
			Writer::printLine("You have to defeat it before you can continue");
		}

		Writer::printLongLine();
		return;
	}
}

void Game::grab(Command cmd) {
	if (player.getCurrentRoom()->hasEnemy()) {
		Writer::printLongLine();
		Writer::printSpc();
		Writer::printEmpty(5);
		Writer::printLine("You have to eliminate your enemy first!");
		Writer::printLongLine();
		return;
	}

	if (!cmd.hasSecondWord()) {
		Writer::printLongLine();
		Writer::printSpc();
		for (int i = 0; i < player.getCurrentRoom()->getInventory()->getSize(); i++) {
			if (player.getInventory()->addItem(player.getCurrentRoom()->getInventory()->getItem(i))) {
				Writer::printEmpty(5);
				Writer::printLine(Writer::append("You grabbed a: ", player.getCurrentRoom()->getInventory()->getItem(i)->getItemName()));
				player.getCurrentRoom()->getInventory()->removeItem(i);
			}
		}
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
				Writer::printLongLine();
				Writer::printEmpty(5);
				Writer::printLine("You drank a Health Potion");
				Writer::printSpc();
				Writer::printEmpty(5);
				Writer::printLine(Writer::append(Writer::append("Health: ", std::to_string(oldHealth)), Writer::append(" >> ", std::to_string(player.getHealth()))));
				Writer::printLongLine();
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

	if (!player.isAlive()) {
		Writer::printLongLine();
		Writer::printSpc();
		Writer::printEmpty(5);
		Writer::printLine("Player has died!");
		Writer::printLongLine();
		return wantToQuit;
	}

	if(cmd.isUnknown()) {
		Writer::printLongLine();
		Writer::printSpc();
		Writer::printEmpty(5);
		Writer::printLine("I don't know what you mean...");
		Writer::printLongLine();
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
	else if (commandWord.compare("attack") == 0) {
		this->attack(cmd);
		//If player is fighting a enemy, let the enmy do a strike
		if (player.getCurrentRoom()->hasEnemy()) {
			this->counterAttack();
		}
	}

	return wantToQuit;
}

void Game::printWelcome()
{
	std::cout << std::endl;
	Writer::printLongLine();
	Writer::printSpc();
	Writer::printEmpty(5);
	Writer::printLine("Welcome to JailBreak, type help for commands...");
	Writer::printSpc();
	Writer::printEmpty(5);
	Writer::printLine("You are locked in a cel, you have to break out and kill the warden...");
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

void Game::attack(Command cmd) {
	if (player.getCurrentRoom()->hasEnemy()) {
		if (!cmd.hasSecondWord()) {
			// if there is no second word, we use fists
			player.attack(player.getCurrentRoom()->getEnemy(), 5);
			Writer::printLongLine();
			Writer::printSpc();
			Writer::printEmpty(5);
			Writer::printLine("You punched the enemy in his face");
			Writer::printSpc();
			Writer::printEmpty(5);
			Writer::printLine("You have dealt: 5");
			Writer::printEmpty(5);
			Writer::printLine(Writer::append("Your Health: ", std::to_string(player.getHealth())));
			Writer::printEmpty(5);
			Writer::printLine(Writer::append("Enemy Health: ", std::to_string(player.getCurrentRoom()->getEnemy()->getHealth())));
			Writer::printLongLine();
		}
		else {
			std::string weaponString = cmd.getSecondWord();

			//Check the inventory for the weapon
			bool weaponFound = false;
			for (int i = 0; i < player.getInventory()->getSize(); i++) {
				if (player.getInventory()->getItem(i)->getItemName() == weaponString) {
					Weapon* sword = dynamic_cast<Weapon*>(player.getInventory()->getItem(i));
					player.attack(player.getCurrentRoom()->getEnemy(), sword->getAttackDamage());
					Writer::printLongLine();
					Writer::printSpc();
					Writer::printEmpty(5);
					Writer::printLine(sword->getRandomAttackPhrase());
					Writer::printSpc();
					Writer::printEmpty(5);
					Writer::printLine(Writer::append("You have dealt: ", std::to_string(sword->getAttackDamage())));
					Writer::printEmpty(5);
					Writer::printLine(Writer::append("Your Health: ", std::to_string(player.getHealth())));
					Writer::printEmpty(5);
					Writer::printLine(Writer::append("Enemy Health: ", std::to_string(player.getCurrentRoom()->getEnemy()->getHealth())));
					Writer::printLongLine();
					weaponFound = true;
				}
			}

			if (!weaponFound) {
				Writer::printLongLine();
				Writer::printSpc();
				Writer::printEmpty(5);
				Writer::printLine("You dont have that weapon!");
				Writer::printLongLine();
			}
		}
		

		if (!player.getCurrentRoom()->getEnemy()->isAlive()) {
			Writer::printLongLine();
			Writer::printSpc();
			Writer::printEmpty(5);
			Writer::printLine(Writer::append("Your Health: ", std::to_string(player.getHealth())));
			Writer::printEmpty(5);
			Writer::printLine("You have eliminated your enemy!");
			Writer::printLongLine();

			player.getCurrentRoom()->killCurrentEnemy();
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
	int damage = rand() % player.getCurrentRoom()->getEnemy()->getMaxDamage() + player.getCurrentRoom()->getEnemy()->getMinDamage();
	player.getCurrentRoom()->getEnemy()->attack(&this->player, damage);

	Writer::printLongLine();
	Writer::printSpc();
	Writer::printEmpty(5);
	Writer::printLine(Writer::append("Enemy has dealt: ", std::to_string(damage)));
	Writer::printEmpty(5);
	Writer::printLine(Writer::append("Your Health: ", std::to_string(player.getHealth())));
	Writer::printEmpty(5);
	Writer::printLine(Writer::append("Enemy Health: ", std::to_string(player.getCurrentRoom()->getEnemy()->getHealth())));
	Writer::printLongLine();
}

