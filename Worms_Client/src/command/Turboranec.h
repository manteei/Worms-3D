#pragma once

#include "Actions.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <GL/glu.h>
using namespace sf;

class Turboranec : public Actions {
	Clock timer;
public:

	void execute() override {
		
		std::cout << "Выполнена команда 1" << std::endl;

	}
};