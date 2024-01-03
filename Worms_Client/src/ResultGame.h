#pragma once
#include <iostream>
#include "InitText.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>
using namespace sf;

class ResultGame
{
	InitText initText;
	Text Titul, Yes;
public:
	bool needClose = false;
	ResultGame();
	void gameIsLost();
};

