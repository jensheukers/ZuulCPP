// room.cpp
#include "stdafx.h"
#include "room.h"
#include "writer.h"

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

std::vector<std::string> Room::getInventoryItems()
{
	std::vector<std::string> invItems;
	
	for (int i = 0; i < this->inventory->getSize(); i++) {
		invItems.push_back(this->inventory->getItem(i)->getItemName());
	}

	return invItems;
}

Inventory* Room::getInventory() {
	return this->inventory;
}
