// room.cpp
#include "stdafx.h"
#include "room.h"

Room::Room(std::string desc)
{
	this->description = desc;
}

Room::~Room()
{

}

void Room::setExit(std::string direction, Room* neighbor)
{
	exits[direction] = neighbor;
}

Room* Room::getExit(std::string direction)
{
	if (exits.find(direction) != exits.end()) {
		return exits[direction];
	}
	return NULL;
}

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

std::string Room::getInventoryString()
{
	std::string returnString = "Items: ";
	
	for (int i = 0; i < this->inventory->getSize(); i++) {
		returnString.append(this->inventory->getItem(i)->getItemName());
		returnString.append(", ");
	}

	return returnString;
}

Inventory* Room::getInventory() {
	return this->inventory;
}
