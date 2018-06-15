#pragma once
#include <iostream>
#include <string>
#include <vector>
class Entity {
public:
	void damage(int amount);
	bool isAlive();
	void heal(int amount);
	int getHealth();
	void attack(Entity* other, int damage);
	int getMinDamage() { return this->minDamage; }
	int getMaxDamage() { return this->maxDamage; }
	std::string getName() { return this->name; }
protected:
	const int MAX_HEALTH = 100;
	const int MIN_HEALTH = 0;
	int health = 100;
	int minDamage = 0;
	int maxDamage = 1;
	std::string name = "Entity";
};