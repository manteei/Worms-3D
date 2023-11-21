#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <GL/glu.h>
#include "player.h"
#include "map.h"
using namespace sf;

class Camera
{
public:

    
    float x, y, z, speed;
    float dx, dy, dz;
    float w, h, d;
    bool onGround, farPlayer;
   

    Camera(Player player);
    void update(float time,Player player);
    void keyboard();
   
};