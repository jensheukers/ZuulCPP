#include "stdafx.h"
#include "player.h"

/**
* Returns the current room player is in
*/
Room* Player::getCurrentRoom() {
	return this->currentRoom;
}

/**
* Sets the current room for the player
*/
Room* Player::setCurrentRoom(Room* room) {
	this->currentRoom = room;
	return this->currentRoom;
}

/**
* Returns the player's Inventory instance
*/
Inventory* Player::getInventory() {
	return this->inventory;
}

/**
* Checks if player has given Item
*/
bool Player::hasItem(Item* item) {
	for (int i = 0; i < this->getInventory()->getSize(); i++) {
		if (item->getItemName() == this->getInventory()->getItem(i)->getItemName()) {
			return true;
		}
	}
	return false;
}