#include "player.h"

int Player::generateRandomNumber() {
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<int> distribution(500, 700); 

    return distribution(gen);
}
Player& Player::operator=(const Player& other)
{
    if (this != &other)
    {
        // ����������� ������ ������
        name = other.name;
        x = other.x;
        y = other.y;
        z = other.z;
        dx = other.dx;
        dy = other.dy;
        dz = other.dz;
        w = other.w;
        h = other.h;
        d = other.d;
        onGround = other.onGround;
        needJump = other.needJump;
        flying = other.flying;
        onSand = other.onSand;
        canShoot = other.canShoot;
        speed = other.speed;
        size = other.size;
        PI = other.PI;
        health = other.health;
        damage = other.damage;

        // ����������� ������ � ��� ��������
        t = other.t;

        // ��������, ��� � other.t ���������� �����
        if (other.t.getFont())
        {
            // ����������� ������, ���� �� ����������
            t.setFont(*other.t.getFont());
        }
    }
    return *this;
}

Player::Player(float size0)
{
    x = generateRandomNumber(); y = generateRandomNumber(); z = generateRandomNumber();
    dx = 0; dy = 0; dz = 0;
    w = 5; h = 10; d = 5;
    onGround = flying = needJump = false;
    size = size0;
    onSand = true;
}

void Player::load(Font& font)
{
    t.setFont(font);
    t.setString(name);
    t.setFillColor(sf::Color::Red);
}
void Player::setFlying(bool fly) {
    flying = fly;
}
void Player::update(Time time, std::vector < std::vector<std::vector<bool>>>& mass, Map map)
{
    needJump = false;
    if (!onGround) dy -= time.asSeconds() * 100;
    onGround = 0;

    x += dx * time.asSeconds() * 100;
    collision(dx, 0, 0, mass, map);
    y += dy * time.asSeconds() * 100;
    collision(0, dy, 0, mass, map);
    z += dz * time.asSeconds() * 100;
    collision(0, 0, dz, mass, map);

    dx = dz = 0;
}

void Player::draw(RenderWindow& window)
{
    window.draw(t);
};

void Player::setPosition(float x1, float y1, float z1)
{
    x = x1;
    y = y1;
    z = z1;
}

void Player::collision(float Dx, float Dy, float Dz, std::vector < std::vector<std::vector<bool>>>& mass, Map map)
{
    float minX = map.minX;
    float minY = map.minY;
    float minZ = map.minZ;
    float maxX = map.maxX * size;
    float maxY = map.maxY * size;
    float maxZ = map.maxZ * size;
    float granica = minY * size + 120;

    if (x - w + Dx < minX) {
        x = minX + w;
    }
    if (x + w + Dx > maxX) {
        x = maxX - w;

    }
    if (y + h + Dy < minY) {
        y = minY + h;
    }
   
    if (y + h + Dy > maxY) {
        y = maxY - h;
    }
    if (z - d + Dz < minZ) {
        z = minZ + d;
    }
    if (z + d + Dz > maxZ) {
        z = maxZ - d;
    }
    if ((y + h + Dy > granica) and onSand and !flying) {
        y = granica;
    }
   
    if ((y + h + Dy > granica) and flying) {
        onSand = false;
    }
    if ((y + h + Dy < granica) ) {
        onSand = true;
    }

    for (int X = (x - w) / size; X < (x + w) / size; X++)
        for (int Y = (y - h) / size; Y < (y + h) / size; Y++)
            for (int Z = (z - d) / size; Z < (z + d) / size; Z++)
                if (check(X, Y, Z, mass)) {
                    if (Dx > 0) {
                        x = X * size - w; needJump = true;
                    }
                    if (Dx < 0) {
                        x = X * size + size + w; needJump = true;
                    }
                    if (Dy > 0)  y = Y * size - h;
                    if (Dy < 0) { y = Y * size + size + h; onGround = true; dy = 0; }
                    if (Dz > 0) { z = Z * size - d; needJump = true; }
                    if (Dz < 0) { z = Z * size + size + d; needJump = true; }
                }
}

bool Player::check(int x, int y, int z, std::vector < std::vector<std::vector<bool>>>& mass)
{
    if ((x < 0) || (x >= 64 * size) ||
        (y < 0) || (y >= 15 * size) ||
        (z < 0) || (z >= 64 * size)) return false;

    return mass[x][y][z];
}



void Player::keyboard(float angleX)
{


    if (Keyboard::isKeyPressed(Keyboard::W))
    {
        dx = -sin(angleX / 180 * PI);
        dz = -cos(angleX / 180 * PI);
        if (needJump) {

            onGround = false; dy = size / 5;

        }
        if (flying) { dx *= size / 10; dz *= size / 10; }
    }

    if (Keyboard::isKeyPressed(Keyboard::S))
    {
        dx = sin(angleX / 180 * PI);
        dz = cos(angleX / 180 * PI);
        if (needJump) {

            onGround = false; dy = size / 5;

        }
        if (flying) { dx *= size / 10; dz *= size / 10; }
    }

    if (Keyboard::isKeyPressed(Keyboard::D))
    {
        dx = sin((angleX + 90) / 180 * PI);
        dz = cos((angleX + 90) / 180 * PI);
        if (needJump) {

            onGround = false; dy = size / 5;

        }
        if (flying) { dx *= size / 10; dz *= size / 10; }
    }

    if (Keyboard::isKeyPressed(Keyboard::A))
    {
        dx = sin((angleX - 90) / 180 * PI);
        dz = cos((angleX - 90) / 180 * PI);
        if (needJump) {

            onGround = false; dy = size / 5;

        }
        if (flying) { dx *= size / 10; dz *= size / 10; }
    }

    if (Keyboard::isKeyPressed(Keyboard::Space) and flying)
    {
        dy = size / 5;
        
    }

};