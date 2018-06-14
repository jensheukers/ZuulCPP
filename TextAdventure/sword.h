#include "weapon.h"
#pragma once
class Sword : public Weapon {
public:
	Sword() {
		attackDamage = 29;
		itemName = "Sword";
		weight = 10;
	};
};