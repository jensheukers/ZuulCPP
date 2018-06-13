#include "item.h"
#pragma once
class Key : public Item {
public:
	Key() {
		itemName = "Key";
		weight = 1;
	};
};