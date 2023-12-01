#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "InitText.h"

using namespace sf;

class About_Game
{
    Texture texture_ab;
    Font font;
    Text Titul;
public:
    About_Game();
    void showInformation();
};

