#include "weapon.h"
#pragma once
class Sword : public Weapon {
public:
	Sword() {
		attackDamage = 29;
		itemName = "Sword";
		weight = 10;
		attackPhrases.push_back("You stabbed the enemy in the chest");
		attackPhrases.push_back("You ran around the enemy then stabbed him in the back");
		attackPhrases.push_back("You threw your sword right in the enemy's eye.");
	};
};