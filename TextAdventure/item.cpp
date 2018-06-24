#include "stdafx.h"
#include "items.h"

/**
* Returns the weight of current Item instance.
*/
int Item::getWeight() {
	return this->weight;
}

/**
* Returns the name string of current Item instance.
*/
std::string Item::getItemName() {
	return this->itemName;
}