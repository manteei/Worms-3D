#include "Options.h"


Options::Options(RenderWindow& window)
	:mywindow(window)
{

}

void Options::show()
{

	//RenderWindow options(VideoMode(400, 400), L"Настройки", Style::None);
	////options.setVerticalSyncEnabled(true);
	//RectangleShape background_ab(Vector2f(400, 400));


	/*Texture texture_ab;
	if (!texture_ab.loadFromFile("resources/container.png")) exit(3);
	background_ab.setTexture(&texture_ab);*/

	//Texture t;
	//t.loadFromFile("resources/container.png");
	//Sprite s(t);
	//s.setOrigin(8, 8); s.setPosition(400, 400);

	//
	//while (mywindow.isOpen())
	//{

	//	Event event_opt;
	//	while (mywindow.pollEvent(event_opt))
	//	{
	//		if (event_opt.type == Event::Closed) mywindow.close();
	//		if (event_opt.type == Event::KeyPressed)
	//		{
	//			if (event_opt.key.code == Keyboard::Escape) mywindow.close();
	//		}
	//	}

	//	
	//	mywindow.clear();
	//	mywindow.draw(s);
	//	mywindow.display();
	//}

}
