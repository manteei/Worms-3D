#include "ConfirmClosure.h"

ConfirmClosure::ConfirmClosure(){}

void ConfirmClosure::showConfirmClosure() {
    RenderWindow close(sf::VideoMode(460, 200), L"Окно подтверждения при закрытии", Style::None);
    ShowCursor(TRUE);
    close.setMouseCursorVisible(true);
    
    initText.texts(Titul, 10, 30, L"Вы уверены, что хотите закрыть игру?", 24, Color::Black, 1, Color::White);
   
    RectangleShape yesButton(Vector2f(100, 50));
    yesButton.setPosition(110, 120);
    yesButton.setFillColor(Color(84, 92, 103));
    initText.texts(Yes, 148, 130, L"Да", 22, Color::Black, 1, Color::White);

    RectangleShape noButton(Vector2f(100, 50));
    noButton.setPosition(255, 120);
    noButton.setFillColor(Color(84, 92, 103));
    initText.texts(No, 290, 130, L"Нет", 22, Color::Black,1,Color::White);
    while (close.isOpen()) {
        sf::Event event;
        while (close.pollEvent(event)) {
             if (event.type == Event::MouseButtonReleased) {
                Vector2i mousePos = Mouse::getPosition(close);
                if (yesButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    needClose = true;
                    close.close();
                }
                else if (noButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    close.close();
                }
            }
        }

        close.clear(Color(160, 156, 144));
        close.draw(Titul);
        close.draw(yesButton);
        close.draw(noButton);
        close.draw(Yes);
        close.draw(No);
        close.display();
    }
}