#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class InitText
{
	Font font;

public:
	InitText();
	void texts(Text& mtext, float xpos, float ypos, String str, int size_font = 60,
		Color menu_text_color = Color::White, int bord = 0, Color border_color = Color::Black);
	void timer(Text& mtext, float xpos, float ypos, int str, int size_font = 60,
		Color menu_text_color = Color::White, int bord = 0, Color border_color = Color::Black);
};

