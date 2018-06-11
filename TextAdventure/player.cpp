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