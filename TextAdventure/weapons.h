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
	std::string getRandomAttackPhrase() {
		int randChosen = rand() % attackPhrases.size();

		return attackPhrases[randChosen];
	};

protected:
	int attackDamage = 0;
	std::vector<std::string>attackPhrases;
};

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

class Wrench : public Weapon {
public:
	Wrench() {
		attackDamage = 29;
		itemName = "Wrench";
		weight = 10;
		attackPhrases.push_back("You stabbed the enemy in the chest");
		attackPhrases.push_back("You ran around the enemy then stabbed him in the back");
		attackPhrases.push_back("You threw your sword right in the enemy's eye.");
	};
};