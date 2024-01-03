#include "Health.h"
void Health::setRecrangleHealth(RectangleShape& health, float xpos, float ypos)
{
	RectangleShape healthBarEnemy(Vector2f(200, 20));
	
	healthBarEnemy.setFillColor(Color(109, 185, 102));
	healthBarEnemy.setPosition(xpos, ypos);
	health = healthBarEnemy;

}

Health::Health(RenderWindow& window)
	:mywindow(window) {}

void Health::updateHealth(Player player, std::vector<Player> enemyVec) {
	max_menu = enemyVec.size()+1;
	namePlayer = new Text[max_menu];
	healthBar = new RectangleShape[max_menu];
	barWidth = new float[max_menu];

	

	for (int i = 0, ypos = 755; i < max_menu; i++, ypos -= 50) {
		if (i == 0) {
			setRecrangleHealth(healthBar[i], 100, ypos);
			initText.texts(namePlayer[i], 20, ypos, player.name, 20, Color::Black);
			if (player.health <= 0) barWidth[i] = 0;
			else barWidth[i] = (player.health / maxHealth) * 200;
		}
		else {
			setRecrangleHealth(healthBar[i], 100, ypos);
			initText.texts(namePlayer[i], 20, ypos, enemyVec[i-1].name, 20, Color::Black);
			if (enemyVec[i - 1].health <= 0) barWidth[i] = 0;
			else barWidth[i] = (enemyVec[i-1].health / maxHealth) * 200;
		}
		healthBar[i].setSize(Vector2f(barWidth[i], 20));
	}
}


void Health::draw()
{
	for (int i = 0; i < max_menu; i++) {
		mywindow.draw(healthBar[i]);
		mywindow.draw(namePlayer[i]);
	}
}