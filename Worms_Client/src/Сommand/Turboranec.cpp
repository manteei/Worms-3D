#include "Turboranec.h"

void Player::keyboard(float angleX)
{
    if (Keyboard::isKeyPressed(Keyboard::Space)) if (onGround) { onGround = false; dy = size * 2; };

    if (Keyboard::isKeyPressed(Keyboard::W))
    {
        dx = -sin(angleX / 180 * PI);
        dz = -cos(angleX / 180 * PI);
        if (needJump) {
            onGround = false; dy = size / 4;
        }
    }

    if (Keyboard::isKeyPressed(Keyboard::S))
    {
        dx = sin(angleX / 180 * PI);
        dz = cos(angleX / 180 * PI);
        if (needJump) {
            onGround = false; dy = size / 4;
        }
    }

    if (Keyboard::isKeyPressed(Keyboard::D))
    {
        dx = sin((angleX + 90) / 180 * PI);
        dz = cos((angleX + 90) / 180 * PI);
        if (needJump) {
            onGround = false; dy = size / 4;
        }
    }

    if (Keyboard::isKeyPressed(Keyboard::A))
    {
        dx = sin((angleX - 90) / 180 * PI);
        dz = cos((angleX - 90) / 180 * PI);
        if (needJump) {
            onGround = false; dy = size / 4;
        }
    }



};

void Turboranec::startFlight() {
      
}