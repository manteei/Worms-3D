#include "GameMenu.h"

void GameMenu::AlignMenu(int posx)
{
	float nullx = 0;
	for (int i = 0; i < max_menu; i++) {
		switch (posx)
		{
		case 0:
			nullx = 0; 
		case 1:
			nullx = mainMenu[i].getLocalBounds().width;  
			break;
		case 2:
			nullx = nullx = mainMenu[i].getLocalBounds().width / 2;  
			break;
		}
		mainMenu[i].setPosition(mainMenu[i].getPosition().x - nullx, mainMenu[i].getPosition().y);
	}

}

GameMenu::GameMenu(RenderWindow& window, float menux, float menuy,
	int index, String name[], int sizeFont, int step)
	:mywindow(window), menu_X(menux), menu_Y(menuy), size_font(sizeFont), menu_Step(step)
{

	max_menu = index; 
	mainMenu = new Text[max_menu];   
	// Выстраиваем элементы меню
	for (int i = 0, ypos = menu_Y; i < max_menu; i++, ypos += menu_Step)
		initText.texts(mainMenu[i], menu_X, ypos, name[i], size_font, menu_text_color, 3, border_color);
	mainMenuSelected = 1; 
	mainMenu[mainMenuSelected].setFillColor(chose_text_color);
	
}

void GameMenu::MoveUp()
{
	mainMenuSelected--;
	if (mainMenuSelected >= 0) {
		mainMenu[mainMenuSelected].setFillColor(chose_text_color);
		mainMenu[mainMenuSelected + 1].setFillColor(menu_text_color);
	}
	else
	{
		mainMenu[0].setFillColor(menu_text_color);
		mainMenuSelected = max_menu - 1;
		mainMenu[mainMenuSelected].setFillColor(chose_text_color);
	}
}
void GameMenu::MoveDown()
{
	mainMenuSelected++;
	if (mainMenuSelected < max_menu) {
		mainMenu[mainMenuSelected - 1].setFillColor(menu_text_color);
		mainMenu[mainMenuSelected].setFillColor(chose_text_color);
	}
	else
	{
		mainMenu[max_menu - 1].setFillColor(menu_text_color);
		mainMenuSelected = 0;
		mainMenu[mainMenuSelected].setFillColor(chose_text_color);
	}

}
void GameMenu::draw()
{	
	for (int i = 0; i < max_menu; i++) mywindow.draw(mainMenu[i]);
}

void GameMenu::setColorTextMenu(Color menColor, Color ChoColor, Color BordColor)
{
	menu_text_color = menColor;   
	chose_text_color = ChoColor; 
	border_color = BordColor;   

	for (int i = 0; i < max_menu; i++) {
		mainMenu[i].setFillColor(menu_text_color);
		mainMenu[i].setOutlineColor(border_color);
	}

	mainMenu[mainMenuSelected].setFillColor(chose_text_color);
}