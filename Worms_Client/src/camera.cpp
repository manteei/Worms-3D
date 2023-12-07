#include "camera.h"

Camera::Camera(Player player)
{
    x = player.x; y = player.y; z = player.z;
    dx = 0; dy = 0; dz = 0;
    w = 5; h = 20; d = 5;
    farPlayers = 0;
    farPlayer = false;
    onGround = true;

}

void Camera::update(Time time, Player player)
{
    if (!onGround) dy -= time.asSeconds() * 50;

    onGround = 0;
    y += dy * time.asSeconds() * 50;
    if (y + h + dy < player.y) { y = player.y; }
    if (y + h + dy > 600) { y = 600 - h; }
    if (farPlayer) farPlayers = 60;
    else farPlayers = 0;;

    x = player.x;  z = player.z;
}


void Camera::keyboard()
{

    if (Keyboard::isKeyPressed(Keyboard::E))
    {
        onGround = false; dy = 20;
    }

    if (Keyboard::isKeyPressed(Keyboard::F5))
    {
        farPlayer = !farPlayer;
    }



};


