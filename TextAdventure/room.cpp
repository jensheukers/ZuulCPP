// room.cpp
#include "stdafx.h"
#include "room.h"
#include "writer.h"

/**
* Constructor.
*/
Room::Room(std::string desc)
{
	this->description = desc;
}

/**
* Destructor
*/
Room::~Room()
{

}


/**
* Sets an exit for the room.
*/
void Room::setExit(std::string direction, Room* neighbor)
{
	exits[direction] = neighbor;
}

/**
* Returns the current set exit
*/
Room* Room::getExit(std::string direction)
{
	if (exits.find(direction) != exits.end()) {
		return exits[direction];
	}
	return NULL;
}

/**
* Returns the exit string
*/
std::string Room::getExitString()
{
	std::string returnString = "Exits: ";
	std::map<std::string,Room*>::iterator it = exits.begin();
	while (it != exits.end()) {
		returnString += it->first;
		returnString += " ";
		++it;
	}

	return returnString;
}

/**
* Returns a vector with all the inventory items
*/
std::vector<std::string> Room::getInventoryItems()
{
	std::vector<std::string> invItems;
	
	for (int i = 0; i < this->inventory->getSize(); i++) {
		invItems.push_back(this->inventory->getItem(i)->getItemName());
	}

	return invItems;
}

/**
* Returns the inventory vector instance
*/
Inventory* Room::getInventory() {
	return this->inventory;
}

/**
* Locks/Unlocks the room
*/
void Room::setLock(bool state) {
	this->locked = state;
}

/**
* Set the required key Item type, that is needed to unlock the door
*/
void Room::setRequiredKey(Item* key) {
	this->requiredKey = key;
}

/**
* Attemps to unlock the door if the user has the right key item
*/
void Room::unlock(Item* keyItem) {
	if (keyItem->getItemName() == this->requiredKey->getItemName()) {
		setLock(false);
	}
}

/**
* Returns the current lock state
*/
bool Room::getLockState() {
	if (this->locked) {
		return true;
	}
	return false;
}

/**
* Returns the current key name
*/
std::string Room::getKeyName() {
	return this->requiredKey->getItemName();
}

/**
* Gets the current key Item instance.
*/
Item* Room::getKey() {
	return this->requiredKey;
}

/**
* Sets the current room's enemy, can be any Entity.
*/
void Room::setEnemy(Entity* enemy) {
	this->enemy = enemy;
	this->hasEnemyActive = true;
}

/**
* Returns true if room has a enemy, otherwise returns false.
*/
bool Room::hasEnemy() {
	return this->hasEnemyActive;
}

/**
* Returns the current room Entity instance.
*/
Entity* Room::getEnemy() {
	return this->enemy;
}

/**
* Kills the current room enemy
*/
void Room::killCurrentEnemy() {
	if (hasEnemyActive) {
		this->enemy = nullptr;
		this->hasEnemyActive = false;
	}
}