#include "items.h"
#pragma once
class Weapon : public Item {
public:
	Weapon() {
		itemName = "Weapon";
		weight = 5;
		type = "weapon";
	};

	int getAttackDamageMax() {
		return this->attackDamageMax;
	}
	int getAttackDamageMin() {
		return  this->attackDamageMin;
	}

	std::string getRandomAttackPhrase() {
		int randChosen = rand() % attackPhrases.size();

		return attackPhrases[randChosen];
	};

protected:
	int attackDamageMax = 0;
	int attackDamageMin = 0;
	std::vector<std::string>attackPhrases;
};

class Sword : public Weapon {
public:
	Sword() {
		attackDamageMax = 35;
		attackDamageMin = 20;
		itemName = "Sword";
		weight = 10;
		attackPhrases.push_back("You stabbed the enemy in the chest");
		attackPhrases.push_back("You ran around the enemy then stabbed him in the back");
		attackPhrases.push_back("You threw your sword right in the enemy's eye.");
	};
};

class Wrench : public Weapon {
public:
	Wrench() {
		attackDamageMax = 20;
		attackDamageMin = 7;
		itemName = "Wrench";
		weight = 10;
		attackPhrases.push_back("You punched the enemy with the wrench");
		attackPhrases.push_back("You jumped in the air and hit the enemy on his head");
		attackPhrases.push_back("You poked the enemy with your wrench");
	};
};