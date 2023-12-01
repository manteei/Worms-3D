#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class GameMenu
{
	float menu_X;                   // Координаты меню по X
	float menu_Y;				    // Координаты меню по Y
	int menu_Step;                  // Расстояние между пунктами меню
	int max_menu;                   // Максимальное количество пунктов меню
	int size_font;                  // Размер шрифта
	int mainMenuSelected;           // Номер текущего пункта меню 
	Font font;                  // Шрифт меню 
	// Динамический массив текстовых объектов названий пунктов меню
	Text* mainMenu;
	Color menu_text_color = Color::White;    // Цвет пунктов меню
	Color chose_text_color = Color::Yellow;  // Цвет выбора пункта меню
	Color border_color = Color::Black;       // Цвет обводки текста пунктов меню

	// Настройка текста пунктов меню
	// Параметры: ссылка на текстовый объект, текст, координаты текста
	void setInitText(Text& text, String str, float xpos, float ypos);
	// Ссылка на графическое окно
	RenderWindow& mywindow;
public:
	// Конструктор 
	// Параметры: ссылка на графическое окно, координаты игрового меню по x и y
	// количество пунктов меню, массив названий пунктов меню, размер шрифта, шаг между пунктами меню
	GameMenu(RenderWindow& window, float menux, float menuy,
		int index, String name[], int sizeFont = 60, int step = 80);

	~GameMenu()
	{
		delete[] mainMenu;
	}

	void draw();        // Рисуем меню

	void MoveUp();     // Перемещение выбора меню вверх

	void MoveDown();   // Перемещение выбора меню вниз

	// Цвет элементов игрового меню
	void setColorTextMenu(Color menColor, Color ChoColor, Color BordColor);

	void AlignMenu(int posx);   // Выравнивание положения меню

	int getSelectedMenuNumber() // Возвращает номер выбранного элемента меню
	{
		return mainMenuSelected;
	}
};