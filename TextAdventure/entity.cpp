#include "stdafx.h"
#include "entity.h"

/**
* Damage the entity.
*/
void Entity::damage(int amount) {
	if (this->health - amount < 0) {
		this->health = 0;
		return;
	}
	this->health -= amount;
}

/**
* Heal the entity
*/
void Entity::heal(int amount) {
	if (this->health < 100) {
		this->health += amount;
	}
}

/**
* Get the enemy's health
*/
int Entity::getHealth() {
	return this->health;
}

/**
* Returns true if entity is alive
*/
bool Entity::isAlive() {
	if (this->health > 0) {
		return true;
	}
	return false;
}

/**
* Attacks the entity
*/
void Entity::attack(Entity* other, int damage) {
	other->damage(damage);
}