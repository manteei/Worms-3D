#include "camera.h"

Camera::Camera(Player player)
{
    x = player.x; y = player.y; z = player.z;
    dx = 0; dy = 0; dz = 0;
    w = 5; h = 20; d = 5;
    farPlayer = false;
    onGround = true;

}

void Camera::update(Time time, Player player)
{
    if (!onGround) dy -= time.asSeconds()* 100;
 
    onGround = 0;
    y += dy * time.asSeconds()*100;
    if (y + h + dy < player.z) {y = player.y; }
    if (y + h + dy > 600) {y = 600 - h;}
    if (farPlayer) h = 60;
    else h = player.h;

    x = player.x;  z = player.z;
}


void Camera::keyboard()
{

    if (Keyboard::isKeyPressed(Keyboard::E))
    {
        onGround = false; dy = 40;
    }

    if (Keyboard::isKeyPressed(Keyboard::F5))
    {
        farPlayer = !farPlayer;
    }



};


