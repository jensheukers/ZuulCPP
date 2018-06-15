#pragma once
#include "entity.h"

class Guard : public Entity {
public:
	Guard() {
		this->minDamage = 4;
		this->maxDamage = 16;
		this->name = "Guard";
	}
};