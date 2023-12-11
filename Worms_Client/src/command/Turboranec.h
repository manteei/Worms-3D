#pragma once

#include "Actions.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <GL/glu.h>
#include "../player.h"
#include "../camera.h"
using namespace sf;

class Turboranec : public Actions {

public:

	void execute(Player& player, Camera& camera) override {
		player.flying = true;
	}
};