#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class GameMenu
{
	float menu_X;                   // ���������� ���� �� X
	float menu_Y;				    // ���������� ���� �� Y
	int menu_Step;                  // ���������� ����� �������� ����
	int max_menu;                   // ������������ ���������� ������� ����
	int size_font;                  // ������ ������
	int mainMenuSelected;           // ����� �������� ������ ���� 
	Font font;                  // ����� ���� 
	// ������������ ������ ��������� �������� �������� ������� ����
	Text* mainMenu;
	Color menu_text_color = Color::White;    // ���� ������� ����
	Color chose_text_color = Color::Yellow;  // ���� ������ ������ ����
	Color border_color = Color::Black;       // ���� ������� ������ ������� ����

	// ��������� ������ ������� ����
	// ���������: ������ �� ��������� ������, �����, ���������� ������
	void setInitText(Text& text, String str, float xpos, float ypos);
	// ������ �� ����������� ����
	RenderWindow& mywindow;
public:
	// ����������� 
	// ���������: ������ �� ����������� ����, ���������� �������� ���� �� x � y
	// ���������� ������� ����, ������ �������� ������� ����, ������ ������, ��� ����� �������� ����
	GameMenu(RenderWindow& window, float menux, float menuy,
		int index, String name[], int sizeFont = 60, int step = 80);

	~GameMenu()
	{
		delete[] mainMenu;
	}

	void draw();        // ������ ����

	void MoveUp();     // ����������� ������ ���� �����

	void MoveDown();   // ����������� ������ ���� ����

	// ���� ��������� �������� ����
	void setColorTextMenu(Color menColor, Color ChoColor, Color BordColor);

	void AlignMenu(int posx);   // ������������ ��������� ����

	int getSelectedMenuNumber() // ���������� ����� ���������� �������� ����
	{
		return mainMenuSelected;
	}
};