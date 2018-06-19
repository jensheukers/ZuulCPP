#pragma once
#include "inventory.h"
#include "room.h"
#include "entity.h"
class Player : public Entity {
public:
	Room* getCurrentRoom();
	Room* setCurrentRoom(Room* room);
	Inventory* getInventory();
	bool hasItem(Item* item);
	void setCurrentEquiped(Item* item) {
		this->currentEquiped = item;
	}
	Item* getCurrentEquiped() {
		return this->currentEquiped;
	}
private:
	Inventory* inventory = new Inventory();
	bool Fighting = false;
	Entity* currentEnemy = nullptr;
	Room* currentRoom = nullptr;
	Item* currentEquiped = nullptr;
};