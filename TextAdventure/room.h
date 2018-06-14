// room.h

#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <map>
#include <string>
#include "inventory.h"
#include "entity.h"

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
	void setLock(bool state);
	void setRequiredKey(Item* key);
	void unlock(Item* keyItem);
	bool getLockState();
	std::string getKeyName();
	Item* getKey();
	
	void setEnemy(Entity* enemy);
	Entity* getEnemy();
	bool hasEnemy();

private:
	bool locked = false;
	bool hasEnemyActive = false;
	Item* requiredKey = new Item();
	Entity* enemy = new Entity();
	std::string description;
	std::map<std::string, Room*> exits;
	Inventory* inventory = new Inventory();
};

#endif /* ROOM_H */
