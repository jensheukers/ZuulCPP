#include "stdafx.h"
#include "inventory.h"

std::vector<Item*> Inventory::getContents() {
	return this->contents;
}

Item* Inventory::getItem(int index) {
	return this->contents[index];
}

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

void Inventory::removeItem(int index) {
	this->weight -= this->getItem(index)->getWeight();
	this->contents.erase(this->contents.begin() + index);
}

int Inventory::getWeight() {
	return this->weight;
}

int Inventory::getSize() {
	return this->contents.size();
}

int Inventory::getMaxWeight() {
	return maxWeight;
}
int Inventory::setMaxWeight(int max) {
	this->maxWeight = max;
	return maxWeight;
}