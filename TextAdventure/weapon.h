#include "item.h"
#pragma once
class Weapon : public Item {
public:
	Weapon() {
		itemName = "Weapon";
		weight = 5;
	};
	int getAttackDamage() {
		return this->attackDamage;
	}

protected:
	int attackDamage = 0;
};