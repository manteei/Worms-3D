#include "enemy.h"

Enemy::Enemy(float x0, float y0, float z0, float size0)
{
    x = x0; y = y0; z = z0;
    size = size0;
}

void Enemy::load(Font& font)
{
	t.setFont(font);
	t.setString(name);
	t.setFillColor(Color::Red);
}

void Enemy::draw(RenderWindow& window)
{
	window.draw(t);
};