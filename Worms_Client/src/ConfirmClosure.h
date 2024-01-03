#pragma once
#include <iostream>
#include "InitText.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>
using namespace sf;

class ConfirmClosure
{
	InitText initText;
	Text Titul,Yes,No;
public:
	bool needClose = false;
	ConfirmClosure();
	void showConfirmClosure();
};

