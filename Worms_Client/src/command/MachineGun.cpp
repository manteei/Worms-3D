#pragma once
#include "Actions.cpp"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <GL/glu.h>
#include "../player.h"
#include "../camera.h"
using namespace sf;
class MachineGun : public Actions
{
public:
	void execute(Player& player, Camera& camera) override {
		player.canShoot = true;
		player.damage = 10;
		std::cout << " sdfsd" << std::endl;

	}
};

