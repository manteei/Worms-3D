#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;


class Enemy
{
public:
    Text t;
 
    float x, y, z;
    float size;
    std::string name;
    Enemy(float x0, float y0, float z0, float size0);
    void load(Font& font);
    void draw(RenderWindow& window);
};

