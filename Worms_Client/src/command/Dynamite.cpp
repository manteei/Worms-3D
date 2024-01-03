#pragma once
#include "Actions.cpp"
#include <iostream>
#include "../player.h"
#include "../camera.h"
using namespace sf;

class Dynamite : public Actions
{
public:
	void execute(Player& player, Camera& camera) override {
		player.canShoot = true;
		player.damage = 20;
	}
};
