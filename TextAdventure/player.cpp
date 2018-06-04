#include "stdafx.h"
#include "player.h"

Room* Player::getCurrentRoom() {
	return this->currentRoom;
}

Room* Player::setCurrentRoom(Room* room) {
	this->currentRoom = room;
	return this->currentRoom;
}

std::string Player::getInventoryString()
{
	std::string returnString = "Items: ";

	for (int i = 0; i < this->inventory->getSize(); i++) {
		returnString.append(this->inventory->getItem(i)->getItemName());
		returnString.append(", ");
	}

	return returnString;
}

Inventory* Player::getInventory() {
	return this->inventory;
}