#include "About_Game.h"

About_Game::About_Game() {

}
// Функция с описанием игры
void About_Game::showInformation()
{
 
    RenderWindow About(VideoMode::getDesktopMode(), L"О игре", Style::Fullscreen);
    RectangleShape background_ab(Vector2f(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height));
    About.setMouseCursorVisible(false);
    if (!texture_ab.loadFromFile("resources/3.jpg")) exit(3);
    background_ab.setTexture(&texture_ab);

    initText.texts(Titul, 600, 400, L"ляляля игра наверное супер\n      никогда не играли", 50, Color(255, 239, 213), 3);


    while (About.isOpen())
    {
        Event event_play;
        while (About.pollEvent(event_play))
        {
            if (event_play.type == Event::Closed) About.close();
            if (event_play.type == Event::KeyPressed)
            {
                if (event_play.key.code == Keyboard::Escape) About.close();
            }
        }
        About.clear();
        About.draw(background_ab);
        About.draw(Titul);
        About.display();
    }
}