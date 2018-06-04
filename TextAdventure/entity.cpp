#include "stdafx.h"
#include "entity.h"

void Entity::damage(int amount) {
	if (this->health - amount < 0) {
		this->health = 0;
		return;
	}
	this->health -= amount;
}

void Entity::heal(int amount) {
	if (this->health < 100) {
		this->health += amount;
	}
}

int Entity::getHealth() {
	return this->health;
}

bool Entity::isAlive() {
	if (this->health > 0) {
		return true;
	}
	return false;
}

void Entity::attack(Entity* other, int damage) {
	other->damage(damage);
}