#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class InitText
{
public:
	InitText();
	void texts(Text& mtext, float xpos, float ypos, String str, int size_font = 60,
		Color menu_text_color = Color::White, int bord = 0, Color border_color = Color::Black);

};

