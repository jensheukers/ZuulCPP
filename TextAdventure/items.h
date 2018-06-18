#pragma once
#include <iostream>
#include <vector>

class Item {
public:
	int getWeight();
	std::string getItemName();
	virtual ~Item() {};
protected:
	int weight = 1;
	std::string itemName = "Item";
};

class Key : public Item {
public:
	Key() {
		itemName = "Key";
		weight = 1;
	};
};

class HealthPotion : public Item {
public:
	HealthPotion() {
		itemName = "HealthPotion";
		weight = 2;
	};
};