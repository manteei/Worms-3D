#include "Options.h"


void Options::setInitButton(RectangleShape& button, Texture& texture, String& file, float xpos, float ypos)
{
	RectangleShape button0(Vector2f(50, 50));
	texture.loadFromFile(file);
	
	button0.setPosition(xpos, ypos);
	button0.setOutlineThickness(3);
	button0.setOutlineColor(Color::Black);
	button0.setTexture(&texture);
	button = button0;
	
}


Options::Options(RenderWindow& window, float menux, float menuy,
	int index, String name[], String file[], int sizeFont, int step)
	:mywindow(window), menu_X(menux), menu_Y(menuy), size_font(sizeFont), menu_Step(step)
{
	max_menu = index; 
	mainMenu = new RectangleShape[max_menu];     
	nameTools = new Text[max_menu];
	texture = new Texture[max_menu];
	int i = 0;

	for (int ypos = menu_Y; ypos < 960 and i < max_menu; ypos += menu_Step)
		for (int xpos = menu_X; xpos < 1800 and i < max_menu; xpos += menu_Step) {
			setInitButton(mainMenu[i], texture[i], file[i], xpos, ypos);
			initText.texts(nameTools[i], menu_X, menu_Y - 70, name[i], size_font, menu_text_color, 2, menu_text_color_border);
			i++;
		}
	
	mainMenuSelected = 0; 
	mainMenu[mainMenuSelected].setOutlineColor(chose_text_color_border);
	initText.texts(Titul, 1520, 950, L"чтобы выбрать,нажмите Enter", 20, Color::Black);

}

void Options::MoveUp()
{
	mainMenuSelected -= 5;
	if (mainMenuSelected >= 0) {
		mainMenu[mainMenuSelected].setOutlineColor(chose_text_color_border);
		mainMenu[mainMenuSelected + 5].setOutlineColor(menu_text_color_border);
	}
	else
	{
		mainMenu[mainMenuSelected + 5].setOutlineColor(menu_text_color_border);
		mainMenuSelected = max_menu +1 + mainMenuSelected;
		if (mainMenuSelected == max_menu) mainMenuSelected -= 5;
		mainMenu[mainMenuSelected].setOutlineColor(chose_text_color_border);
	}
}
void Options::MoveLeft()
{
	mainMenuSelected--;
	if (mainMenuSelected >= 0) {
		mainMenu[mainMenuSelected].setOutlineColor(chose_text_color_border);
		mainMenu[mainMenuSelected + 1].setOutlineColor(menu_text_color_border);
	}
	else
	{
		mainMenu[0].setOutlineColor(menu_text_color_border);
		mainMenuSelected = max_menu - 1;
		mainMenu[mainMenuSelected].setOutlineColor(chose_text_color_border);
	}
}
void Options::MoveRight()
{
	mainMenuSelected++;
	if (mainMenuSelected < max_menu) {
		mainMenu[mainMenuSelected - 1].setOutlineColor(menu_text_color_border);
		mainMenu[mainMenuSelected].setOutlineColor(chose_text_color_border);
	}
	else
	{
		mainMenu[max_menu - 1].setOutlineColor(menu_text_color_border);
		mainMenuSelected = 0;
		mainMenu[mainMenuSelected].setOutlineColor(chose_text_color_border);
	}
}
void Options::MoveDown()
{
	mainMenuSelected += 5;
	if (mainMenuSelected < max_menu) {
		mainMenu[mainMenuSelected - 5].setOutlineColor(menu_text_color_border);
		mainMenu[mainMenuSelected].setOutlineColor(chose_text_color_border);
	}
	else
	{
		mainMenu[mainMenuSelected - 5].setOutlineColor(menu_text_color_border);
		mainMenuSelected = mainMenuSelected%5;
		mainMenu[mainMenuSelected].setOutlineColor(chose_text_color_border);
	}

}
// рисуем элементы меню в графическом окне
void Options::draw()
{	
	for (int i = 0; i < max_menu; i++) mywindow.draw(mainMenu[i]);

	mywindow.draw(nameTools[mainMenuSelected]);
	mywindow.draw(Titul);
}
