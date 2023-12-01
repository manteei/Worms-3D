#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <GL/glu.h>
#include "player.h"

using namespace sf;

class Options
{
    RenderWindow& mywindow;
public:
    Options(RenderWindow& window);
    void show();

};
