#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <GL/glu.h>
#include "map.h"

using namespace sf;

class Player
{
public:
    Text t;
    std::string name;
    float x, y, z;
    float dx, dy, dz;
    float w, h, d;
    bool onGround, needJump;
    float speed, size;
    const float PI = 3.141592653;
    Player(float size0);
    void update(Time time, std::vector < std::vector<std::vector<bool>>>& mass, Map map);
    void collision(float Dx, float Dy, float Dz, std::vector < std::vector<std::vector<bool>>>& mass, Map map);
    void keyboard(float angleX);
    bool check(int x, int y, int z, std::vector < std::vector<std::vector<bool>>>& mass);
    void setPosition(float x1, float y1, float z1);
    void load(Font& font);
    void draw(RenderWindow& window);
};

