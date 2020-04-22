#pragma once

#include "Factory.h"

class CharacterFactory : public Factory
{
public:
	Character* CreateBee() {
		return new Bee;
	}
};