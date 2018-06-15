#pragma once
#include "entity.h"

class Roamer : public Entity {
public:
	Roamer() {
		this->minDamage = 1;
		this->maxDamage = 8;
		this->name = "Roamer";
	}
};