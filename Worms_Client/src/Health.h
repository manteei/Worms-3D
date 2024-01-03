#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <GL/glu.h>
#include "player.h"
#include "InitText.h"
using namespace sf;

class Health
{
	InitText initText;
	float* barWidth;
	int max_menu;
	float maxHealth = 100.0f;
	Text* namePlayer;
	RectangleShape* healthBar;
	RenderWindow& mywindow;
	void setRecrangleHealth(RectangleShape& button, float xpos, float ypos);
public:
	Health(RenderWindow& window);
	void updateHealth(Player player, std::vector<Player> enemyVec);
	void draw();
	~Health()
	{
		delete[] healthBar;
	}
};

