// room.h

#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <map>
#include <string>
#include "inventory.h"

class Room
{
public:
	Room(std::string desc);
	virtual ~Room();

	void setExit(std::string direction, Room* neighbor);
	Room* getExit(std::string direction);

	std::string getLongDescription() { return "You are " + description; }
	std::string getExitString();
	Inventory* getInventory();
	std::vector<std::string> getInventoryItems();

private:
	std::string description;
	std::map<std::string, Room*> exits;
	Inventory* inventory = new Inventory();
};

#endif /* ROOM_H */
