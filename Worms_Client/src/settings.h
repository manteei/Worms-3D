#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "InitText.h"

using namespace sf;

class Settings
{
    Texture texture_ab;
    InitText initText;
    Text Titul,Titul2;
    Text inputText;
    std::string name;
    bool nameCreated = false;
public:
    Settings();
    void inputName();
    std::string getName();
};

