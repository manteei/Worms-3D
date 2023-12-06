#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <GL/glu.h>
#include "map.h"

using namespace sf;

class Player
{
    float x, y, z;
    float dx, dy, dz;
    float w, h, d;
    bool onGround, needJump;
    float speed, size, health;
public:
    Text t;
    std::string name;
    const float PI = 3.141592653;
    Player(float size0);
    void update(Time time, std::vector < std::vector<std::vector<bool>>>& mass, Map map);
    void collision(float Dx, float Dy, float Dz, std::vector < std::vector<std::vector<bool>>>& mass, Map map);
    void keyboard(float angleX);
    bool check(int x, int y, int z, std::vector < std::vector<std::vector<bool>>>& mass, float maxX, float maxY, float maxZ);
    void setPosition(float x1, float y1, float z1);
    void load(Font& font);
    void draw(RenderWindow& window);
    float getPosX();
    float getPosY();
    float getPosZ();
    float getPosH();
};

