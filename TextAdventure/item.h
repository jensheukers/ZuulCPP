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