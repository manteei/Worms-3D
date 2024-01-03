#include "ResultGame.h"

ResultGame::ResultGame() {}

void ResultGame::gameIsLost() {
    RenderWindow close(sf::VideoMode(460, 200), L"Окно проигравшего", Style::None);
    ShowCursor(TRUE);
  //  close.setMouseCursorVisible(true);

    initText.texts(Titul, 90, 30, L"Вы проиграли, увы..", 30, Color::Black, 1, Color::White);

    RectangleShape yesButton(Vector2f(250, 50));
    yesButton.setPosition(110, 120);
    yesButton.setFillColor(Color(84, 92, 103));
    initText.texts(Yes, 148, 130, L"Выйти из игры", 22, Color::Black, 1, Color::White);

    while (close.isOpen()) {
        Event event;
        while (close.pollEvent(event)) {
            if (event.type == Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Return) {
                    needClose = true;
                    close.close();
                }
            }

            if (event.type == Event::MouseButtonReleased) {
                Vector2i mousePos = Mouse::getPosition(close);
                if (yesButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    needClose = true;
                    close.close();
                }
            }

            Vector2i mousePos = Mouse::getPosition(close);
            if (yesButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                yesButton.setFillColor(Color::Red);
            }
            else {
                yesButton.setFillColor(Color(84, 92, 103));
            }

            
        }

        close.clear(Color(160, 156, 144));
        close.draw(Titul);
        close.draw(yesButton);
        close.draw(Yes);
        close.display();
    }
}