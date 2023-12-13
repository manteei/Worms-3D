#pragma once
#include "../player.h"
#include "../camera.h"
class Actions {
public:

	virtual void execute(Player& player, Camera& camera) = 0;
};