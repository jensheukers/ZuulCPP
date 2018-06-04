#include "item.h"
#pragma once
class HealthPotion : public Item {
public:
	HealthPotion() {
		itemName = "HealthPotion";
		weight = 2;
	};
};