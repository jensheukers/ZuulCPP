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