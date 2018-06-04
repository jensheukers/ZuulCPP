#pragma once
class Entity {
public:
	void damage(int amount);
	bool isAlive();
	void heal(int amount);
	int getHealth();
	void attack(Entity* other, int damage);
protected:
	const int MAX_HEALTH = 100;
	const int MIN_HEALTH = 0;
	int health = 100;
};