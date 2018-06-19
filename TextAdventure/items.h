#pragma once
#include <iostream>
#include <vector>

class Item {
public:
	int getWeight();
	std::string getItemName();
	virtual ~Item() {};
	std::string getType() {
		return type;
	}
protected:
	int weight = 1;
	std::string itemName = "Item";
	std::string type = "item";
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

class Soap : public Item {
public:
	Soap() {
		itemName = "Soap";
		weight = 20;
	};
};