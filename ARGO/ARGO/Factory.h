#pragma once

#include "Bee.h"

class Factory {
public:
	virtual Character* CreateBee() = 0;
};