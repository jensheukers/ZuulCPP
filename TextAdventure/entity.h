#pragma once
#include <iostream>
#include <string>
class Entity {
public:
	void damage(int amount);
	bool isAlive();
	void heal(int amount);
	int getHealth();
	void attack(Entity* other, int damage);
	std::string getName() { return this->name; }
protected:
	const int MAX_HEALTH = 100;
	const int MIN_HEALTH = 0;
	int health = 100;
	int minDamage = 0;
	int maxDamage = 0;
	std::string name = "Entity";
};