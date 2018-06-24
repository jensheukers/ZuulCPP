#include "stdafx.h"
#include "inventory.h"

/**
* Returns all the inventory contents.
*/
std::vector<Item*> Inventory::getContents() {
	return this->contents;
}

/**
* Returns the given Item relative to the index.
*/
Item* Inventory::getItem(int index) {
	return this->contents[index];
}

/**
* Adds a Item to the inventory vector, if inventory is not full.
*/
bool Inventory::addItem(Item* item) {
	//TODO: Calculate weights

	if (this->weight + item->getWeight() <= maxWeight) {
		this->weight += item->getWeight();
		this->contents.push_back(item);
		return true;
	}
	std::cout << "Inventory is full!" << std::endl;
	return false;
}

/**
* Removes a item from the vector list
*/
void Inventory::removeItem(int index) {
	this->weight -= this->getItem(index)->getWeight();
	this->contents.erase(this->contents.begin() + index);
}

/**
* Gets the current inventory weight.
*/
int Inventory::getWeight() {
	return this->weight;
}

/**
* Gets the size of the contents vector
*/
int Inventory::getSize() {
	return this->contents.size();
}

/**
* Gets the maximum weight allowed for the inventory
*/
int Inventory::getMaxWeight() {
	return maxWeight;
}

/**
* Set the maximum weight for the inventory.
*/
int Inventory::setMaxWeight(int max) {
	this->maxWeight = max;
	return maxWeight;
}