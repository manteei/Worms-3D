#pragma once
#include "../player.h"
class Actions {
public:

	virtual void execute(Player& player) = 0;
};