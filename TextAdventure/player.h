#pragma once
#include "inventory.h"
#include "room.h"
#include "entity.h"
class Player : public Entity {
public:
	Room* getCurrentRoom();
	Room* setCurrentRoom(Room* room);
	Inventory* getInventory();
	std::string getInventoryString();
private:
	Inventory* inventory = new Inventory();
	bool Fighting = false;
	Entity* currentEnemy = nullptr;
	Room* currentRoom = nullptr;
};