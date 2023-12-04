#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <GL/glu.h>
#include "player.h"
#include "InitText.h"

using namespace sf;

class Options
{
	float menu_X;                  
	float menu_Y;				   
	int menu_Step;                 
	int max_menu;                  
	int size_font;                
	int mainMenuSelected;          
	Font font;  
	Text Titul;
	InitText initText;
	// Динамический массив текстовых объектов названий пунктов меню
	RectangleShape* mainMenu;


	Color menu_text_color_border = Color::Black;    
	Color chose_text_color_border = Color::Red;  
	Color menu_text_color = Color(237, 147, 0);
	Text* nameTools;
	String* fileTools;
	Texture* texture;
	
	void setInitButton(RectangleShape& button, Texture& texture, String& text, float xpos, float ypos);
	RenderWindow& mywindow;
public:
	
	Options(RenderWindow& window, float menux, float menuy,
		int index, String name[], String file[], int sizeFont = 60, int step = 80);

	~Options()
	{
		delete[] mainMenu;
	}

	void draw();        

	void MoveUp();     
	void MoveDown();   
	void MoveLeft();     
	void MoveRight();  

	

	int getSelectedMenuNumber() // Возвращает номер выбранного элемента меню
	{
		return mainMenuSelected;
	}

	bool showWindow = false;
};
