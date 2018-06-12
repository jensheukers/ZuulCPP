#include "stdafx.h"
#include "player.h"

Room* Player::getCurrentRoom() {
	return this->currentRoom;
}

Room* Player::setCurrentRoom(Room* room) {
	this->currentRoom = room;
	return this->currentRoom;
}

Inventory* Player::getInventory() {
	return this->inventory;
}

bool Player::hasItem(Item* item) {
	for (int i = 0; i < this->getInventory()->getSize(); i++) {
		if (item->getItemName() == this->getInventory()->getItem(i)->getItemName()) {
			return true;
		}
	}
	return false;
}