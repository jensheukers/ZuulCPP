#include "item.h"
#pragma once
class Weapon : public Item {
public:
	int attackDamage = 0;
	Weapon() {
		itemName = "Weapon";
		weight = 5;
	};
};