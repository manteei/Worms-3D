#pragma once

#include "Actions.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <GL/glu.h>
#include "../player.h"

using namespace sf;

class Turboranec : public Actions {
	Clock timer;
public:

	void execute(Player& player) override {
		player.flying = true;
	}
};